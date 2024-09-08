#include "Child.h"

#include <filesystem>
#include <nlohmann/json.hpp>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include "../../logging/Log.h"
#include "../../logging/LogColor.h"
#include "../../utils/DirectoryUtils.h"
#include "../../utils/TimeUtils.h"
#include "../Program.h"
#include "../settings/enums/Activity.h"
#include "../settings/enums/LoggingOptions.h"
#include "media/Media.h"

std::vector<std::thread> workerThreads;

void Child::prepare(void) {
  std::vector<std::filesystem::directory_entry> files =
      DirectoryUtils::getFilesInCWDWithExt(std::vector{".mkv", ".avi"});

  for (std::filesystem::directory_entry file : files) {
    std::string cwd = file.path().parent_path().string();
    std::string filename = file.path().filename().string();

    Media* media = new Media(filename, cwd);
    media->file->rename();

    if (!std::filesystem::exists(media->file->conversionFolderPath)) {
      Log::debug({"[Child.cpp] Creating directory: ",
                  media->file->conversionFolderPath});
      std::filesystem::create_directory(media->file->conversionFolderPath);
    }

    this->pending.push(media);
  }
}

void Child::run(void) {
  // once every second
  this->setEndable(false);
  int currentAmount = static_cast<int>(this->converting.size());

  Program::log->debug(
      {"[Ticker.cpp]", std::to_string(currentAmount),
       std::to_string(Program::settings->argumentParser->amount)});

  if ((currentAmount < Program::settings->argumentParser->amount) &&
      !this->pending.empty()) {
    Media* media = this->pending.front();

    // if there are no media files waiting
    // and the current amount of converting media is 0
    // then exit the program
    if (!media->isWaiting()) {
      Program::log->debug({"[Ticker.cpp] Media is not waiting:",
                           media->file->originalFileNameExt,
                           Activity::getValue(media->getActivity())});
      if (currentAmount == 0) {
        this->setEndable(true);
        Program::stopFlag = true;
      }
    } else {
      Log::debug({"[Ticker.cpp] Queued media for encoding:",
                  media->file->originalFileNameExt,
                  Activity::getValue(media->getActivity())});
      media->setActivity(Activity::WAITING_STATISTICS);

      media->started = TimeUtils::getEpoch();

      this->converting.push(media);
      this->pending.pop();
    }

    this->setEndable(true);
  }

  // error if there are more converting than allowed
  if (currentAmount > Program::settings->argumentParser->amount) {
    Program::log->send({LogColor::fgRed(
        "CURRENT TRANSCODES ARE GREATER THAN THE ALLOWED AMOUNT.")});

    Program::log->send({LogColor::fgRed(
        "CURRENT ALLOWED AMOUNT: " +
        std::to_string(Program::settings->argumentParser->amount))});

    Program::log->send({LogColor::fgRed(
        "CURRENT QUEUE: " +
        std::to_string(Program::settings->argumentParser->amount))});

    // iterate over converting
    while (!this->converting.empty()) {
      Media* value = this->converting.front();
      Program::log->send(
          {LogColor::fgRed("CURRENT FILE: " + value->file->conversionName)});
      this->converting.pop();
    }
  }

  // temp queue for conversion iteration
  std::queue<Media*> t_queue;

  // iterate over converting media
  while (!this->converting.empty()) {
    Media* media = this->converting.front();

    Program::log->debug({"[Ticker.cpp]", media->file->originalFileNameExt,
                         Activity::getValue(media->getActivity())});

    if (!media->isProcessing()) {
      Program::log->debug({"[Ticker.cpp] Media is not processing:",
                           media->file->originalFileNameExt,
                           Activity::getValue(media->getActivity())});
      if (media->isWaitingToStatistics())
        media->doStatistics();
      else if (media->isWaitingToConvert()) {
        media->buildFFmpegArguments(false);

        workerThreads.emplace_back([media]() { media->doConversion(); });

      } else if (media->isWaitingToValidate()) {
        workerThreads.emplace_back([media]() { media->doValidation(); });
      }
    }

    if (media->hasFailed() || media->hasFinished()) {
      // todo: again, chrono stuff
      media->ended = TimeUtils::getEpoch();

      Program::log->debug(
          {"[Ticker.cpp] Media ended:", media->file->conversionName});
      this->pending.push(media);
      Program::log->debug({"[Ticker.cpp] pending size after finish:",
                           std::to_string(this->pending.size())});
    } else {
      t_queue.push(media);
    }
    this->converting.pop();
  }

  Program::log->debug(
      {"[Ticker.cpp] t_queue size:", std::to_string(t_queue.size())});
  this->converting = t_queue;

  if (Program::settings->argumentParser->loggingFormat ==
      LoggingOptions::DEBUG) {
    // Ticker::display->printDebug();
    // should not need to print in this class
  } else if (LoggingOptions::isJSON(
                 Program::settings->argumentParser->loggingFormat)) {
    // Ticker::display->printJSON();
    // should not need to print in this class
  } else {
    // Ticker::display->print();
    // should not need to print in this class
  }
}

void Child::end(void) {
  Log::debug({"[Child.cpp] Ending child runner."});
  Log::debug({"[Child.cpp] Expected to delete { pending[], converting[] }."});
  // iterate over running threads and join
  for (auto& t : workerThreads) {
    if (t.joinable()) {
      t.join();
    }
  }

  // call threads descructor and clear the vector
  workerThreads.clear();

  // iterate over pending
  while (!this->pending.empty()) {
    Media* media = this->pending.front();
    this->pending.pop();

    Program::log->debug(
        {"[Child.cpp] Deleting media in:", media->file->originalFileNameExt});

    delete media;
  }

  // iterate over converting
  while (!this->converting.empty()) {
    Media* media = this->converting.front();
    this->converting.pop();

    Program::log->debug(
        {"[Child.cpp] Deleting media in:", media->file->originalFileNameExt});

    delete media;
  }
}

void Child::setEndable(bool flag) {
  Log::debug(
      {"Child has been set as endable:", this->endable ? "True" : "False"});
  this->endable = flag;
}

bool Child::isEndable(void) { return this->endable; }

void Child::fromJSON(nlohmann::json) {}

nlohmann::json Child::asJSON() {
  using namespace nlohmann;

  json child;

  std::queue<Media*> t_queue;

  child["pending"] = nlohmann::json::array();
  child["converting"] = nlohmann::json::array();

  // converting file
  while (!this->converting.empty()) {
    Media* media = this->converting.front();

    nlohmann::json mediaDebug;
    nlohmann::json mediaFileDebug;
    nlohmann::json mediaVideoDebug;
    nlohmann::json mediaWorkingDebug;

    mediaDebug["name"] = media->file->originalFileNameExt;
    mediaDebug["activity"] = Activity::getValue(media->getActivity());
    mediaDebug["path"] = media->file->cwd;
    mediaDebug["started"] = media->started;
    mediaDebug["ended"] = media->ended;
    // this might not work
    mediaDebug["ffmpegArguments"] = media->ffmpegArguments;

    mediaFileDebug["conversionName"] = media->file->conversionName;
    mediaFileDebug["conversionNameExt"] = media->file->conversionNameExt;
    mediaFileDebug["conversionFolderPath"] = media->file->conversionFolderPath;
    mediaFileDebug["conversionFilePath"] = media->file->conversionFilePath;
    mediaFileDebug["ext"] = media->file->ext;
    mediaFileDebug["size"] = media->file->size;
    mediaFileDebug["newSize"] = media->file->newSize;
    mediaFileDebug["validationSize"] = media->file->validationSize;
    mediaFileDebug["path"] = media->file->originalFullPath;
    mediaFileDebug["quality"] = media->file->quality;
    mediaFileDebug["series"] = media->file->series;
    mediaFileDebug["season"] = media->file->season;

    mediaVideoDebug["fps"] = media->video->fps;
    mediaVideoDebug["totalFrames"] = media->video->totalFrames;
    mediaVideoDebug["subtitleProvider"] = media->video->subtitleProvider;
    mediaVideoDebug["width"] = media->video->width;
    mediaVideoDebug["height"] = media->video->height;
    mediaVideoDebug["ratio"] = media->video->ratio;
    mediaVideoDebug["convertedWidth"] = media->video->convertedWidth;
    mediaVideoDebug["convertedHeight"] = media->video->convertedHeight;
    mediaVideoDebug["convertedResolution"] = media->video->convertedResolution;
    mediaVideoDebug["crop"] = media->video->crop;
    mediaVideoDebug["crf"] = media->video->crf;

    mediaWorkingDebug["fps"] = media->working->fps;
    mediaWorkingDebug["completedFrames"] = media->working->completedFrames;
    mediaWorkingDebug["quality"] = media->working->quality;
    mediaWorkingDebug["bitrate"] = media->working->bitrate;

    mediaDebug["file"] = mediaFileDebug;
    mediaDebug["video"] = mediaVideoDebug;
    mediaDebug["working"] = mediaWorkingDebug;

    child["converting"].push_back(mediaDebug);

    this->converting.pop();
    t_queue.push(media);
  }

  this->converting = t_queue;
  t_queue = std::queue<Media*>();

  // pending file
  while (!this->pending.empty()) {
    Media* media = this->pending.front();
    nlohmann::json mediaDebug;
    nlohmann::json mediaFileDebug;
    nlohmann::json mediaVideoDebug;
    nlohmann::json mediaWorkingDebug;

    mediaDebug["name"] = media->file->originalFileNameExt;
    mediaDebug["activity"] = Activity::getValue(media->getActivity());
    mediaDebug["cwd"] = media->file->cwd;
    mediaDebug["started"] = media->started;
    mediaDebug["ended"] = media->ended;
    mediaDebug["ffmpegArguments"] = media->ffmpegArguments;

    mediaFileDebug["conversionName"] = media->file->conversionName;
    mediaFileDebug["conversionNameExt"] = media->file->conversionNameExt;
    mediaFileDebug["conversionFolderPath"] = media->file->conversionFolderPath;
    mediaFileDebug["conversionFilePath"] = media->file->conversionFilePath;
    mediaFileDebug["ext"] = media->file->ext;
    mediaFileDebug["size"] = media->file->size;
    mediaFileDebug["newSize"] = media->file->newSize;
    mediaFileDebug["validationSize"] = media->file->validationSize;
    mediaFileDebug["originalFileNameExt"] = media->file->originalFileNameExt;
    mediaFileDebug["originalFullPath"] = media->file->originalFullPath;
    mediaFileDebug["quality"] = media->file->quality;
    mediaFileDebug["series"] = media->file->series;
    mediaFileDebug["season"] = media->file->season;

    mediaVideoDebug["fps"] = media->video->fps;
    mediaVideoDebug["totalFrames"] = media->video->totalFrames;
    mediaVideoDebug["subtitleProvider"] = media->video->subtitleProvider;
    mediaVideoDebug["width"] = media->video->width;
    mediaVideoDebug["height"] = media->video->height;
    mediaVideoDebug["ratio"] = media->video->ratio;
    mediaVideoDebug["convertedWidth"] = media->video->convertedWidth;
    mediaVideoDebug["convertedHeight"] = media->video->convertedHeight;
    mediaVideoDebug["convertedResolution"] = media->video->convertedResolution;
    mediaVideoDebug["crop"] = media->video->crop;
    mediaVideoDebug["crf"] = media->video->crf;

    mediaWorkingDebug["fps"] = media->working->fps;
    mediaWorkingDebug["completedFrames"] = media->working->completedFrames;
    mediaWorkingDebug["quality"] = media->working->quality;
    mediaWorkingDebug["bitrate"] = media->working->bitrate;

    mediaDebug["file"] = mediaFileDebug;
    mediaDebug["video"] = mediaVideoDebug;
    mediaDebug["working"] = mediaWorkingDebug;

    child["pending"].push_back(mediaDebug);
    this->pending.pop();
    t_queue.push(media);
  }

  this->pending = t_queue;

  return child;
}
