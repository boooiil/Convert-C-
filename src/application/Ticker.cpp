#include "Ticker.h"

#include <fstream>
#include <future>
#include <thread>

#include "../utils/TimeUtils.h"
#include "./Help.h"
#include "nlohmann/json.hpp"

Container* Ticker::container = nullptr;
Display* Ticker::display = nullptr;
std::vector<std::thread> workerThreads;

void Ticker::init() {
  Ticker::container = new Container();
  Ticker::display = new Display(container);
}

void Ticker::determineNextAction() {
  if (container->userSettings.printHelp) {
    Help::printHelp();
  } else if (container->userSettings.printInformation) {
    Ticker::printInformation();
  } else {
    Ticker::start();
  }
  Ticker::end();
}

void Ticker::printInformation() {
  container->log.debug({
      LogColor::fgBlack("Black"),
      LogColor::fgRed("Red"),
      LogColor::fgGreen("Green"),
      LogColor::fgGray("Gray"),
      LogColor::fgYellow("Yellow"),
      LogColor::fgBlue("Blue"),
      LogColor::fgOrange("Orange"),
      LogColor::fgMagenta("Magenta"),
      LogColor::fgCyan("Cyan"),
      LogColor::fgWhite("White"),
  });

  if (container->pending.empty()) {
    container->log.send({LogColor::fgRed("No media files found.")});
    return;
  }

  std::queue<Media*> t_queue;

  while (!container->pending.empty()) {
    Media* media = container->pending.front();
    container->pending.pop();

    media->doStatistics(container);

    std::string nl = "\n";
    std::string ob = LogColor::fgGray("[");
    std::string cb = LogColor::fgGray("]");
    std::string colon = LogColor::fgGray(": ");

    container->log.send(
        {nl + ob + LogColor::fgRed(media->file->originalFileName) + cb + nl});

    container->log.send({LogColor::fgWhite("  " + ob + "Format") + cb});

    container->log.send(
        {LogColor::bgBlue("    Duration") + colon +
         LogColor::bgOrange(media->probeResult->format.duration)});

    container->log.send(
        {LogColor::bgBlue("    Format: ") +
         LogColor::bgOrange(media->probeResult->format.format_name)});

    container->log.send(
        {LogColor::bgBlue("    Bit Rate: ") +
         LogColor::bgOrange(media->probeResult->format.bit_rate)});

    container->log.send({LogColor::bgBlue("    Size: ") +
                         LogColor::bgOrange(media->probeResult->format.size)});

    container->log.send({LogColor::bgBlue("    Stream Count: ") +
                         LogColor::bgOrange(std::to_string(
                             media->probeResult->format.nb_streams))});

    container->log.send(
        {LogColor::fgWhite(nl + "  " + ob + "Video Streams") + cb});

    // video streams
    for (int i = 0; i < media->probeResult->videoStreams.size(); i++) {
      ProbeResultStreamVideo prsv = media->probeResult->videoStreams[i];

      container->log.send({"    " + ob + std::to_string(i) + cb + " " +
                           LogColor::fgOrange(prsv.codec_name)});

      container->log.send(
          {LogColor::fgBlue("      Profile") + colon +
           LogColor::fgOrange(prsv.profile.empty() ? "None" : prsv.profile)});

      container->log.send(
          {LogColor::fgBlue("      Res") + colon +
           LogColor::fgOrange(std::to_string(prsv.width) + "x" +
                              std::to_string(prsv.height)) +
           " (" + LogColor::fgOrange(prsv.display_aspect_ratio) + ")"});

      container->log.send({LogColor::fgBlue("      Listed Duration") + colon +
                           LogColor::fgOrange(prsv.tags.DURATION.empty()
                                                  ? "None"
                                                  : prsv.tags.DURATION)});
    }

    container->log.send(
        {LogColor::fgWhite(nl + "  " + ob + "Audio Streams") + cb});

    // audio streams
    for (int i = 0; i < media->probeResult->audioStreams.size(); i++) {
      ProbeResultStreamAudio prsa = media->probeResult->audioStreams[i];

      container->log.send({"    " + ob + std::to_string(i) + cb + " " +
                           LogColor::fgOrange(prsa.tags.language)});

      container->log.send(
          {LogColor::fgBlue("      Title") + colon +
           LogColor::fgOrange(prsa.tags.title.empty() ? "None"
                                                      : prsa.tags.title)});

      container->log.send({LogColor::fgBlue("      Codec") + colon +
                           LogColor::fgOrange(prsa.codec_name)});

      container->log.send({LogColor::fgBlue("      Channels") + colon +
                           LogColor::fgOrange(std::to_string(prsa.channels))});

      container->log.send({LogColor::fgBlue("      Channel Layout") + colon +
                           LogColor::fgOrange(prsa.channel_layout)});

      container->log.send({LogColor::fgBlue("      Sample Rate") + colon +
                           LogColor::fgOrange(prsa.sample_rate)});

      container->log.send({LogColor::fgBlue("      Bit Rate") + colon +
                           LogColor::fgOrange(prsa.tags.BPS)});
    }

    container->log.send(
        {LogColor::fgWhite(nl + "  " + ob + "Subtitle Streams") + cb});

    // subtitle streams
    for (int i = 0; i < media->probeResult->subtitleStreams.size(); i++) {
      ProbeResultStreamSubtitle prss = media->probeResult->subtitleStreams[i];

      container->log.send({"    " + ob + std::to_string(i) + cb + " " +
                           LogColor::fgOrange(prss.tags.language)});

      container->log.send({LogColor::fgBlue("      Title") + colon +
                           LogColor::fgOrange(prss.tags.title)});

      container->log.send({LogColor::fgBlue("      Codec") + colon +
                           LogColor::fgOrange(prss.codec_name)});
    }

    t_queue.push(media);
  }

  container->converting = t_queue;
};

void Ticker::start() {
  // once every second
  while (true) {
    int currentAmount = static_cast<int>(container->converting.size());

    container->log.debug({"[Ticker.cpp]", std::to_string(currentAmount),
                          std::to_string(container->userSettings.amount)});

    if ((currentAmount < container->userSettings.amount) &&
        !container->pending.empty()) {
      Media* media = container->pending.front();

      if (!media->isWaiting()) {
        container->log.debug({"[Ticker.cpp] Media is not waiting:",
                              media->file->originalFileName,
                              Activity::getValue(media->getActivity())});
        if (currentAmount == 0) {
          container->log.flushBuffer();
          Ticker::end();
          return exit(0);
        }
      } else {
        media->setActivity(Activity::WAITING_STATISTICS);

        media->started = TimeUtils::getEpoch();

        container->converting.push(media);
        container->pending.pop();
      }
    }

    // error if there are more converting than allowed
    if (currentAmount > container->userSettings.amount) {
      container->log.send({LogColor::fgRed(
          "CURRENT TRANSCODES ARE GREATER THAN THE ALLOWED AMOUNT.")});

      container->log.send(
          {LogColor::fgRed("CURRENT ALLOWED AMOUNT: " +
                           std::to_string(container->userSettings.amount))});

      container->log.send({LogColor::fgRed(
          "CURRENT QUEUE: " + std::to_string(container->userSettings.amount))});

      // iterate over converting
      while (!container->converting.empty()) {
        Media* value = container->converting.front();
        container->log.send({LogColor::fgRed("CURRENT FILE: " +
                                             value->file->modifiedFileName)});
        container->converting.pop();
      }
    }

    // temp queue for conversion iteration
    std::queue<Media*> t_queue;

    // iterate over converting media
    while (!container->converting.empty()) {
      Media* media = container->converting.front();

      container->log.debug({"[Ticker.cpp]", media->file->originalFileName,
                            Activity::getValue(media->getActivity())});

      if (!media->isProcessing()) {
        if (media->isWaitingToStatistics())
          media->doStatistics(container);
        else if (media->isWaitingToConvert()) {
          media->buildFFmpegArguments(container, false);

          workerThreads.emplace_back(
              [media]() { media->doConversion(container); });

        } else if (media->isWaitingToValidate()) {
          workerThreads.emplace_back(
              [media]() { media->doValidation(container); });
        }
      }

      if (media->hasFailed() || media->hasFinished()) {
        // todo: again, chrono stuff
        media->ended = TimeUtils::getEpoch();

        container->log.debug(
            {"[Ticker.cpp] Media ended:", media->file->modifiedFileName});
        container->pending.push(media);
        container->log.debug({"[Ticker.cpp] pending size after finish:",
                              std::to_string(container->pending.size())});
      } else {
        t_queue.push(media);
      }
      container->converting.pop();
    }

    container->log.debug(
        {"[Ticker.cpp] t_queue size:", std::to_string(t_queue.size())});
    container->converting = t_queue;

    if (container->userSettings.debug)
      Ticker::display->printDebug();
    else
      Ticker::display->print();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

void Ticker::end() {
  container->log.debug({"[Ticker.cpp] deconstructing ticker"});

  if (container->userSettings.debug) {
    container->log.debug(
        {LogColor::fgRed("Debugging enabled. Writing debug file->")});
    Ticker::writeDebug();
    container->log.debug({LogColor::fgRed("Debug file written.")});
  }

  // iterate over running threads and join
  for (auto& t : workerThreads) {
    if (t.joinable()) {
      t.join();
    }
  }

  // call threads descructor and clear the vector
  workerThreads.clear();

  delete Ticker::display;
  delete Ticker::container;

  exit(0);
}

void Ticker::writeDebug() {
  std::queue<Media*> t_queue;
  nlohmann::json json;

  json["pending"] = nlohmann::json::array();
  json["converting"] = nlohmann::json::array();

  // converting file
  while (!container->converting.empty()) {
    Media* media = container->converting.front();

    nlohmann::json mediaDebug;
    nlohmann::json mediaFileDebug;
    nlohmann::json mediaVideoDebug;
    nlohmann::json mediaWorkingDebug;

    mediaDebug["name"] = media->file->originalFileName;
    mediaDebug["activity"] = Activity::getValue(media->getActivity());
    mediaDebug["path"] = media->file->cwd;
    mediaDebug["started"] = media->started;
    mediaDebug["ended"] = media->ended;
    // this might not work
    mediaDebug["ffmpegArguments"] = media->ffmpegArguments;

    mediaFileDebug["modifiedFileName"] = media->file->modifiedFileName;
    mediaFileDebug["modifiedFileNameExt"] = media->file->modifiedFileNameExt;
    mediaFileDebug["conversionName"] = media->file->conversionName;
    mediaFileDebug["ext"] = media->file->ext;
    mediaFileDebug["size"] = media->file->size;
    mediaFileDebug["newSize"] = media->file->newSize;
    mediaFileDebug["validationSize"] = media->file->validationSize;
    mediaFileDebug["path"] = media->file->originalFullPath;
    mediaFileDebug["conversionPath"] = media->file->conversionPath;
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

    json["converting"].push_back(mediaDebug);

    container->converting.pop();
    t_queue.push(media);
  }

  container->converting = t_queue;
  t_queue = std::queue<Media*>();

  // pending file
  while (!container->pending.empty()) {
    Media* media = container->pending.front();
    nlohmann::json mediaDebug;
    nlohmann::json mediaFileDebug;
    nlohmann::json mediaVideoDebug;
    nlohmann::json mediaWorkingDebug;

    mediaDebug["name"] = media->file->originalFileName;
    mediaDebug["activity"] = Activity::getValue(media->getActivity());
    mediaDebug["path"] = media->file->cwd;
    mediaDebug["started"] = media->started;
    mediaDebug["ended"] = media->ended;
    mediaDebug["ffmpegArguments"] = media->ffmpegArguments;

    mediaFileDebug["modifiedFileName"] = media->file->modifiedFileName;
    mediaFileDebug["modifiedFileNameExt"] = media->file->modifiedFileNameExt;
    mediaFileDebug["conversionName"] = media->file->conversionName;
    mediaFileDebug["ext"] = media->file->ext;
    mediaFileDebug["size"] = media->file->size;
    mediaFileDebug["newSize"] = media->file->newSize;
    mediaFileDebug["validationSize"] = media->file->validationSize;
    mediaFileDebug["path"] = media->file->originalFullPath;
    mediaFileDebug["conversionPath"] = media->file->conversionPath;
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

    json["pending"].push_back(mediaDebug);
    container->pending.pop();
    t_queue.push(media);
  }

  container->pending = t_queue;

  container->log.sendPlain({container->userSettings.quality.get().name});

  json["userSettings"]["wantedEncoder"] =
      container->userSettings.wantedEncoder.get();
  json["userSettings"]["runningEncoder"] =
      container->programSettings.runningEncoder;
  json["userSettings"]["runningDecoder"] =
      container->programSettings.runningDecoder;
  json["userSettings"]["quality"] = container->userSettings.quality.get().name;
  json["userSettings"]["tune"] = container->userSettings.tune;
  json["userSettings"]["amount"] = container->userSettings.amount;
  json["userSettings"]["crfOverride"] = container->userSettings.crfOverride;
  json["userSettings"]["crop"] = container->userSettings.crop;
  json["userSettings"]["startBeginning"] =
      container->userSettings.startBeginning;
  json["userSettings"]["trim"] = container->userSettings.trim.get();
  json["userSettings"]["useBitrate"] = container->userSettings.useBitrate;
  json["userSettings"]["useConstrain"] = container->userSettings.useConstrain;
  json["userSettings"]["validate"] = container->userSettings.validate;
  json["userSettings"]["useHardwareDecode"] =
      container->userSettings.useHardwareDecode;
  json["userSettings"]["useHardwareEncode"] =
      container->userSettings.useHardwareEncode;
  json["userSettings"]["overwrite"] = container->userSettings.overwrite;
  json["userSettings"]["audioStreams"] =
      container->userSettings.audioStreams.get();

  json["settings"]["workingDir"] = container->settings.workingDir;
  json["settings"]["tuneAssociations"] = container->settings.tuneAssociations;

  json["userCapabilities"]["platform"] =
      Platform::getValue(container->userCapabilities.platform);
  json["userCapabilities"]["supportedEncoders"] = nlohmann::json::array();

  // supported encoders
  for (Encoders::Codec codec : container->userCapabilities.supportedEncoders) {
    json["userCapabilities"]["supportedEncoders"].push_back(
        Encoders::getValue(codec));
  }

  // supported decoders
  for (Encoders::Codec codec : container->userCapabilities.supportedEncoders) {
    json["userCapabilities"]["supportedEncoders"].push_back(
        Encoders::getValue(codec));
  }

  json["userCapabilities"]["GPUProvider"] =
      container->userCapabilities.GPU_Provider;

  std::ofstream oFile("container_debug.json");

  if (!oFile.is_open()) {
    container->log.send({LogColor::fgRed("Failed to open debug file->")});
    return;
  }

  oFile << json.dump(4);
  oFile.close();
};