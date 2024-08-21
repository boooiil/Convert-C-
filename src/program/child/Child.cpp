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

Child::Child(void) {}

Child::~Child(void) {}

void Child::prepare(void) {
  std::vector<std::filesystem::directory_entry> files =
      DirectoryUtils::getFilesInCWDWithExt(std::vector{".mkv", ".avi"});

  for (std::filesystem::directory_entry file : files) {
    std::string cwd = file.path().root_directory().string();
    std::string filename = file.path().filename().string();

    Media* media = new Media(filename, cwd);
    media->file->rename();

    this->pending.push(media);
  }
}

void Child::run(void) {
  // once every second
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
      Program::log->debug(
          {"[Ticker.cpp] Media is not waiting:", media->file->originalFileName,
           Activity::getValue(media->getActivity())});
      if (currentAmount == 0) {
        Program::log->flushBuffer();
        Program::end();
      }
    } else {
      Log::debug({"[Ticker.cpp] Queued media for encoding:",
                  media->file->originalFileName,
                  Activity::getValue(media->getActivity())});
      media->setActivity(Activity::WAITING_STATISTICS);

      media->started = TimeUtils::getEpoch();

      this->converting.push(media);
      this->pending.pop();
    }
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
          {LogColor::fgRed("CURRENT FILE: " + value->file->modifiedFileName)});
      this->converting.pop();
    }
  }

  // temp queue for conversion iteration
  std::queue<Media*> t_queue;

  // iterate over converting media
  while (!this->converting.empty()) {
    Media* media = this->converting.front();

    Program::log->debug({"[Ticker.cpp]", media->file->originalFileName,
                         Activity::getValue(media->getActivity())});

    if (!media->isProcessing()) {
      Program::log->debug({"[Ticker.cpp] Media is not processing:",
                           media->file->originalFileName,
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
          {"[Ticker.cpp] Media ended:", media->file->modifiedFileName});
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
  // iterate over running threads and join
  for (auto& t : workerThreads) {
    if (t.joinable()) {
      t.join();
    }
  }

  // call threads descructor and clear the vector
  workerThreads.clear();
}

nlohmann::json Child::asJSON() {
  using namespace nlohmann;

  json child;

  return child;
}
