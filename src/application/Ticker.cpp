#include "Ticker.h"

#include <chrono>
#include <fstream>
#include <thread>

#include "../utils/RegexUtils.h"
#include "./Debug.h"
#include "nlohmann/json.hpp"

Ticker::Ticker(Container& container) : container(container) {
  Ticker::display = new Display(container);
}

Ticker::~Ticker() {
  container.log.debug({"[Ticker.cpp] deconstructing display"});
  Ticker::writeDebug();
  delete Ticker::display;
}

void Ticker::start() {
  // once every second
  while (true) {
    int currentAmount = container.converting.size();

    container.log.send({std::to_string(currentAmount),
                        std::to_string(container.appEncodingDecision.amount)});

    if (currentAmount < container.appEncodingDecision.amount) {
      Media media = container.pending.front();

      if (media.activity != Activity::WAITING) {
        if (currentAmount == 0) {
          container.log.flushBuffer();
          if (Debug::toggle) {
            container.log.debug(
                {LogColor::fgRed("Debugging enabled. Writing debug file.")});
            Ticker::writeDebug();
            container.log.debug({LogColor::fgRed("Debug file written.")});
            exit(0);
          } else
            exit(0);
        }
      } else {
        media.activity = Activity::WAITING_STATISTICS;

        // todo: this is probably going to be an issue at some point?
        // havent tested it, just making predictions
        media.started = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch())
                            .count();

        container.converting[media.name] = media;
        container.pending.pop();
      }
    }

    if (currentAmount > container.appEncodingDecision.amount) {
      container.log.send({LogColor::fgRed(
          "CURRENT TRANSCODES ARE GREATER THAN THE ALLOWED AMOUNT.")});

      container.log.send({LogColor::fgRed(
          "CURRENT ALLOWED AMOUNT: " +
          std::to_string(container.appEncodingDecision.amount))});

      container.log.send({LogColor::fgRed(
          "CURRENT QUEUE: " +
          std::to_string(container.appEncodingDecision.amount))});

      for (auto it = container.converting.begin();
           it != container.converting.end(); ++it) {
        Media value = it->second;
        container.log.send(
            {LogColor::fgRed("CURRENT FILE: " + value.file.modifiedFileName)});
      }
    }

    for (auto it = container.converting.begin();
         it != container.converting.end(); ++it) {
      Media media = it->second;

      container.log.send({media.name, Activity::getValue(media.activity)});

      if (!media.isProcessing()) {
        if (media.activity == Activity::WAITING_STATISTICS)
          media.doStatistics(container);
        if (media.activity == Activity::WAITING_CONVERT)
          media.doConversion(container);
        if (media.activity == Activity::WAITING_VALIDATE)
          media.doValidation(container);
      }

      if (RegexUtils::isMatch(Activity::getValue(media.activity),
                              "finished|failed", std::regex_constants::icase)) {
        // todo: again, chrono stuff
        media.ended = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();
      }
    }

    if (Debug::toggle)
      Ticker::display->printDebug();
    else
      Ticker::display->print();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void Ticker::writeDebug() {
  nlohmann::json json;

  json["pending"] = nlohmann::json::array();

  // converting file
  for (std::pair<std::string, Media> mediaPair : container.converting) {
    Media media = mediaPair.second;

    nlohmann::json mediaDebug;
    nlohmann::json mediaFileDebug;
    nlohmann::json mediaVideoDebug;
    nlohmann::json mediaWorkingDebug;

    mediaDebug["name"] = media.name;
    mediaDebug["activity"] = Activity::getValue(media.activity);
    mediaDebug["path"] = media.file.path;
    mediaDebug["started"] = media.started;
    mediaDebug["ended"] = media.ended;
    // this might not work
    mediaDebug["ffmpegArguments"] = media.ffmpegArguments;

    mediaFileDebug["modifiedFileName"] = media.file.modifiedFileName;
    mediaFileDebug["modifiedFileNameExt"] = media.file.modifiedFileNameExt;
    mediaFileDebug["conversionName"] = media.file.conversionName;
    mediaFileDebug["ext"] = media.file.ext;
    mediaFileDebug["size"] = media.file.size;
    mediaFileDebug["newSize"] = media.file.newSize;
    mediaFileDebug["validationSize"] = media.file.validationSize;
    mediaFileDebug["path"] = media.file.path;
    mediaFileDebug["conversionPath"] = media.file.conversionPath;
    mediaFileDebug["quality"] = media.file.quality;
    mediaFileDebug["series"] = media.file.series;
    mediaFileDebug["season"] = media.file.season;

    mediaVideoDebug["fps"] = media.video.fps;
    mediaVideoDebug["totalFrames"] = media.video.totalFrames;
    mediaVideoDebug["subtitleProvider"] = media.video.subtitleProvider;
    mediaVideoDebug["width"] = media.video.width;
    mediaVideoDebug["height"] = media.video.height;
    mediaVideoDebug["ratio"] = media.video.ratio;
    mediaVideoDebug["convertedWidth"] = media.video.convertedWidth;
    mediaVideoDebug["convertedHeight"] = media.video.convertedHeight;
    mediaVideoDebug["convertedResolution"] = media.video.convertedResolution;
    mediaVideoDebug["crop"] = media.video.crop;
    mediaVideoDebug["crf"] = media.video.crf;

    mediaWorkingDebug["fps"] = media.working.fps;
    mediaWorkingDebug["completedFrames"] = media.working.completedFrames;
    mediaWorkingDebug["quality"] = media.working.quality;
    mediaWorkingDebug["bitrate"] = media.working.bitrate;

    mediaDebug["file"] = mediaFileDebug;
    mediaDebug["video"] = mediaVideoDebug;
    mediaDebug["working"] = mediaWorkingDebug;

    json["converting"][media.name] = mediaDebug;
  }

  // pending file
  while (!container.pending.empty()) {
    Media media = container.pending.front();
    nlohmann::json mediaDebug;
    nlohmann::json mediaFileDebug;
    nlohmann::json mediaVideoDebug;
    nlohmann::json mediaWorkingDebug;

    mediaDebug["name"] = media.name;
    mediaDebug["activity"] = Activity::getValue(media.activity);
    mediaDebug["path"] = media.file.path;
    mediaDebug["started"] = media.started;
    mediaDebug["ended"] = media.ended;
    mediaDebug["ffmpegArguments"] = media.ffmpegArguments;

    mediaFileDebug["modifiedFileName"] = media.file.modifiedFileName;
    mediaFileDebug["modifiedFileNameExt"] = media.file.modifiedFileNameExt;
    mediaFileDebug["conversionName"] = media.file.conversionName;
    mediaFileDebug["ext"] = media.file.ext;
    mediaFileDebug["size"] = media.file.size;
    mediaFileDebug["newSize"] = media.file.newSize;
    mediaFileDebug["validationSize"] = media.file.validationSize;
    mediaFileDebug["path"] = media.file.path;
    mediaFileDebug["conversionPath"] = media.file.conversionPath;
    mediaFileDebug["quality"] = media.file.quality;
    mediaFileDebug["series"] = media.file.series;
    mediaFileDebug["season"] = media.file.season;

    mediaVideoDebug["fps"] = media.video.fps;
    mediaVideoDebug["totalFrames"] = media.video.totalFrames;
    mediaVideoDebug["subtitleProvider"] = media.video.subtitleProvider;
    mediaVideoDebug["width"] = media.video.width;
    mediaVideoDebug["height"] = media.video.height;
    mediaVideoDebug["ratio"] = media.video.ratio;
    mediaVideoDebug["convertedWidth"] = media.video.convertedWidth;
    mediaVideoDebug["convertedHeight"] = media.video.convertedHeight;
    mediaVideoDebug["convertedResolution"] = media.video.convertedResolution;
    mediaVideoDebug["crop"] = media.video.crop;
    mediaVideoDebug["crf"] = media.video.crf;

    mediaWorkingDebug["fps"] = media.working.fps;
    mediaWorkingDebug["completedFrames"] = media.working.completedFrames;
    mediaWorkingDebug["quality"] = media.working.quality;
    mediaWorkingDebug["bitrate"] = media.working.bitrate;

    mediaDebug["file"] = mediaFileDebug;
    mediaDebug["video"] = mediaVideoDebug;
    mediaDebug["working"] = mediaWorkingDebug;

    json["pending"].push_back(mediaDebug);
    container.pending.pop();
  }

  container.log.sendPlain({container.appEncodingDecision.quality});

  json["appEncodingDecision"]["wantedEncoder"] =
      container.appEncodingDecision.wantedEncoder;
  json["appEncodingDecision"]["runningEncoder"] =
      container.appEncodingDecision.runningEncoder;
  json["appEncodingDecision"]["runningDecoder"] =
      container.appEncodingDecision.runningDecoder;
  json["appEncodingDecision"]["quality"] =
      container.appEncodingDecision.quality;
  json["appEncodingDecision"]["tune"] = container.appEncodingDecision.tune;
  json["appEncodingDecision"]["amount"] = container.appEncodingDecision.amount;
  json["appEncodingDecision"]["crfOverride"] =
      container.appEncodingDecision.crfOverride;
  json["appEncodingDecision"]["crop"] = container.appEncodingDecision.crop;
  json["appEncodingDecision"]["startBeginning"] =
      container.appEncodingDecision.startBeginning;
  json["appEncodingDecision"]["trim"] = container.appEncodingDecision.trim;
  json["appEncodingDecision"]["useBitrate"] =
      container.appEncodingDecision.useBitrate;
  json["appEncodingDecision"]["useConstrain"] =
      container.appEncodingDecision.useConstrain;
  json["appEncodingDecision"]["validate"] =
      container.appEncodingDecision.validate;
  json["appEncodingDecision"]["useHardwareDecode"] =
      container.appEncodingDecision.useHardwareDecode;
  json["appEncodingDecision"]["useHardwareEncode"] =
      container.appEncodingDecision.useHardwareEncode;
  json["appEncodingDecision"]["overwrite"] =
      container.appEncodingDecision.overwrite;
  json["appEncodingDecision"]["audioStreams"] =
      container.appEncodingDecision.audioStreams;

  std::ofstream oFile("container_debug.json");

  if (!oFile.is_open()) {
    container.log.send({LogColor::fgRed("Failed to open debug file.")});
    return;
  }

  oFile << json.dump(4);
  oFile.close();
};