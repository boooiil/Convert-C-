/*********************************************************************
 * @file   Media.cpp
 * @brief  Media class implementation file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#include "Media.h"

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../../../logging/Log.h"
#include "../../../utils/ListUtils.h"
#include "../../../utils/StringUtils.h"
#include "../../Program.h"
#include "../../settings/ProgramSettings.h"
#include "../../settings/arguments/ArgumentParser.h"
#include "../../settings/enums/Activity.h"
#include "../../settings/enums/Encoders.h"
#include "../../settings/enums/HWAccelerators.h"
#include "../../settings/enums/Tunes.h"
#include "./MediaProcessConversion.h"
#include "./MediaProcessStatistics.h"
#include "./MediaProcessValidate.h"
#include "MediaFile.h"
#include "MediaFormat.h"
#include "MediaVideoProperties.h"
#include "MediaWorkingProperties.h"

Media::Media()
    : started(0),
      ended(0),
      activity(Activity::WAITING),
      file(new MediaFile()),
      probeResult(nullptr),
      video(new MediaVideoProperties()),
      working(new MediaWorkingProperties()) {
  Log::debug(
      {"[Media.cpp] Constructing blank media (something is not working "
       "properly)."});
}
Media::Media(std::string name, std::string path)
    : started(0),
      ended(0),
      activity(Activity::WAITING),
      file(new MediaFile(name, path)),
      probeResult(nullptr),
      video(new MediaVideoProperties()),
      working(new MediaWorkingProperties()) {}

Media::~Media() {
  Log::debug(
      {"[Media.cpp] Deconstructing media: ", this->file->originalFileNameExt});

  if (file != nullptr) delete file;
  if (video != nullptr) delete video;
  if (working != nullptr) delete working;
  if (probeResult != nullptr) delete probeResult;
}

Activity::ActivityType Media::getActivity() { return Media::activity; }

const bool Media::isProcessing() {
  switch (Media::activity) {
    case Activity::STATISTICS:
    case Activity::CONVERT:
    case Activity::VALIDATE:
      return true;
    default:
      return false;
  }
}

const bool Media::hasFailed() {
  switch (Media::activity) {
    case Activity::FAILED:
    case Activity::FAILED_CODEC:
    case Activity::FAILED_CONTAINER:
    case Activity::FAILED_CORRUPT:
    case Activity::FAILED_FILE:
    case Activity::FAILED_FILE_MISSING:
    case Activity::FAILED_FILE_NOT_RECOGNIZED:
    case Activity::FAILED_FILE_PERMISSIONS:
    case Activity::FAILED_HARDWARE:
    case Activity::FAILED_INVALID_AUDIO_STREAMS:
    case Activity::FAILED_JSON_PARSE:
    case Activity::FAILED_SYSTEM:
      return true;
    default:
      return false;
  }
}

const bool Media::hasFinished() {
  return Media::activity == Activity::FINISHED;
}

const bool Media::isWaiting() { return Media::activity == Activity::WAITING; }

const bool Media::isWaitingToStatistics() {
  return Media::activity == Activity::WAITING_STATISTICS;
}

const bool Media::isWaitingToConvert() {
  return Media::activity == Activity::WAITING_CONVERT;
}

const bool Media::isWaitingToValidate() {
  return Media::activity == Activity::WAITING_VALIDATE;
}

void Media::setActivity(Activity::ActivityType provided_activity) {
  Media::activity = provided_activity;
}

void Media::doStatistics() {
  this->setActivity(Activity::STATISTICS);

  Log::debug({"[Media.cpp] Starting statistics for: ",
              this->file->originalFileNameExt});

  MediaProcessStatistics statistics(this);
  statistics.start(
      "ffprobe -v quiet -print_format json -show_format "
      "-show_streams \"" +
      this->file->originalFullPath + "\"");

  if (this->hasFailed()) {
    return;
  }

  this->setActivity(Activity::WAITING_CONVERT);
}
void Media::doConversion() {
  this->setActivity(Activity::CONVERT);

  Log::debug({"[Media.cpp] Starting conversion for: ",
              this->file->originalFileNameExt});

  MediaProcessConversion conversion(this);

  conversion.start("ffmpeg " + ListUtils::join(Media::ffmpegArguments, " "));

  if (this->hasFailed()) {
    return;
  }

  this->setActivity(Activity::WAITING_VALIDATE);
}
void Media::doValidation() {
  this->setActivity(Activity::VALIDATE);

  Log::debug({"[Media.cpp] Starting validation for: ",
              this->file->originalFileNameExt});

  MediaProcessValidate validate(this);
  validate.start("ffmpeg -v quiet -stats -i \"" +
                 this->file->conversionFilePath + "\" -f null -");

  if (this->hasFailed()) {
    return;
  }

  this->setActivity(Activity::FINISHED);
}

void Media::buildFFmpegArguments(bool isValidate) {
  ArgumentParser argumentParser = *Program::settings->argumentParser;
  ProgramSettings programSettings = *Program::settings->programSettings;
  MediaFormat format = argumentParser.quality;

  this->ffmpegArguments.clear();

  this->ffmpegArguments.push_back("-v error -stats");

  if (argumentParser.useHardwareDecode) {
    if (programSettings.runningHWAccel != HWAccelerators::NONE) {
      this->ffmpegArguments.push_back(
          "-hwaccel " +
          HWAccelerators::getValue(programSettings.runningHWAccel));
    }
  }

  this->ffmpegArguments.push_back("-i \"" + this->file->originalFullPath +
                                  "\"");

  this->ffmpegArguments.push_back("-map 0:v:0");

  if (!argumentParser.audioStreams.get().empty()) {
    for (const int stream : argumentParser.audioStreams.get()) {
      this->ffmpegArguments.push_back("-map 0:a:" + std::to_string(stream));
    }
  } else {
    this->ffmpegArguments.push_back("-map 0:a?");
  }

  this->ffmpegArguments.push_back("-map 0:s?");
  this->ffmpegArguments.push_back("-map 0:t?");

  this->ffmpegArguments.push_back("-c:t copy");

  /***************************************************
   *                                                 *
   *                  AUDIO SETTINGS                 *
   *                                                 *
   ***************************************************/

  // cases:
  // 1. audio streams match audio formats
  // 2. audio streams are greater than audio formats
  // 3. audio streams are less than audio formats
  // 4. audio streams are empty

  // TODO:
  // if audio streams used, iterate only over those audio streams
  // else iterate over all audio streams

  for (int i = 0; i < this->probeResult->audioStreams.size(); i++) {
    if (!argumentParser.audioStreams.get().empty()) {
      if (!ListUtils::contains(argumentParser.audioStreams.get(), i)) continue;
    }

    bool afCopy = false;
    int usingChannels = this->probeResult->audioStreams[i].channels;

    std::string usingFormat = this->probeResult->audioStreams[i].codec_name;

    std::string codecMap = "-c:a:" + std::to_string(i);
    std::string metadataMap = "-metadata:s:a:" + std::to_string(i);
    std::string channelMap = "-ac:a:" + std::to_string(i);

    std::vector<std::string> audioFormats = argumentParser.audioFormats.get();
    std::vector<int> audioChannels = argumentParser.audioChannels.get();

    // if audio formats exceed streams
    // use the format
    if (audioFormats.size() > i) {
      usingFormat = audioFormats[i];
      this->ffmpegArguments.push_back(codecMap + " " + usingFormat);

    }
    // if the formats are not empty
    // but are under the stream count
    // use the last format
    else if (!audioFormats.empty()) {
      usingFormat = audioFormats[audioFormats.size() - 1];
      this->ffmpegArguments.push_back(codecMap + " " + usingFormat);
    }
    // else flag that the audio format is to be copied
    else {
      afCopy = true;
    }

    // if there are provided audio channels
    if (!audioChannels.empty()) {
      // if the audio formats are empty
      // use the existing audio codec
      if (afCopy) {
        std::string codec = this->probeResult->audioStreams[i].codec_name;
        this->ffmpegArguments.push_back(codecMap + " " + codec);
      }

      // if the audio channels exceed the audio streams
      // use the channel at the stream index
      if (audioChannels.size() > i) {
        usingChannels = audioChannels[i];

        this->ffmpegArguments.push_back(channelMap + " " +
                                        std::to_string(usingChannels));
      }
      // else use the last audio channel
      else {
        usingChannels = audioChannels[audioChannels.size() - 1];

        this->ffmpegArguments.push_back(channelMap + " " +
                                        std::to_string(usingChannels));
      }
    } else {
      // if the audio channels are empty
      // and the audio formats are empty
      // copy the existing audio stream
      if (afCopy) {
        this->ffmpegArguments.push_back(codecMap + " copy");
      }
      // if the audio channels are empty
      // and the audio formats are not empty
      // use the default auido channels
      else {
        std::string channels =
            std::to_string(this->probeResult->audioStreams[i].channels);
        this->ffmpegArguments.push_back(channelMap + " " + channels);
      }
    }

    std::string channelType;

    switch (usingChannels) {
      case 1:
        channelType = "Mono";
        break;
      case 2:
        channelType = "Stereo";
        break;
      case 6:
        channelType = "5.1";
        break;
      case 8:
        channelType = "7.1";
        break;
      default:
        channelType = std::to_string(usingChannels);
    }

    usingFormat = StringUtils::toUpperCase(usingFormat);

    this->ffmpegArguments.push_back(metadataMap + " title=\"" + usingFormat +
                                    " " + channelType + "\"");
  }

  this->ffmpegArguments.push_back(
      "-c:v " + Encoders::getValue(programSettings.runningEncoder));

  this->ffmpegArguments.push_back("-preset slow");

  this->ffmpegArguments.push_back("-level 4.1");

  if (argumentParser.useBitrate) {
    this->ffmpegArguments.push_back("-b:v " + std::to_string(format.bitrate) +
                                    "M");
    this->ffmpegArguments.push_back("-bufsize " +
                                    std::to_string(format.bitrate * 2) + "M");
    this->ffmpegArguments.push_back("-maxrate " +
                                    std::to_string(format.max * 2) + "M");
    this->ffmpegArguments.push_back("-minrate " +
                                    std::to_string(format.min * 2) + "M");
  } else if (argumentParser.useConstrain) {
    this->ffmpegArguments.push_back("-crf " + std::to_string(format.crf));
    this->ffmpegArguments.push_back("-bufsize " +
                                    std::to_string(format.bitrate * 2) + "M");
    this->ffmpegArguments.push_back("-maxrate " +
                                    std::to_string(format.max * 2) + "M");
  } else {
    this->ffmpegArguments.push_back("-crf " + std::to_string(format.crf));
  }

  if (argumentParser.crop) {
    this->ffmpegArguments.push_back(
        "-vf scale=" + this->video->convertedResolution +
        ":flags=lanczos,crop=" + format.crop);

  }

  else
    this->ffmpegArguments.push_back(
        "-vf scale=" + this->video->convertedResolution + ":flags=lanczos");

  if (!argumentParser.startBeginning.get().empty()) {
    this->ffmpegArguments.push_back("-ss " +
                                    argumentParser.startBeginning.get());
  }

  if (!argumentParser.trim.get().empty()) {
    this->ffmpegArguments.push_back("-ss " + argumentParser.trim.get()[0]);
    this->ffmpegArguments.push_back("-to " + argumentParser.trim.get()[1]);
  }

  /** TODO: flesh out later */
  // if (this.video.subtitle_provider) {

  //     if (this.video.subtitle_provider === "mov")
  //     this.ffmpeg_argument.push("-c:s mov_text") else
  //     this.ffmpeg_argument.push("-c:s copy")

  // }

  this->ffmpegArguments.push_back("-c:s copy");

  if (argumentParser.tune != Tunes::DEFAULT) {
    this->ffmpegArguments.push_back("-tune " +
                                    Tunes::getValue(argumentParser.tune));
  }

  this->ffmpegArguments.push_back("\"" + this->file->conversionFilePath + "\"");

  if (isValidate || argumentParser.overwrite)
    this->ffmpegArguments.push_back("-y");
  else {
    this->ffmpegArguments.push_back("-n");
  }

  Log::debug(
      {"FFMPEG ARGUMENTS: ", ListUtils::join(this->ffmpegArguments, " ")});
}

const nlohmann::json Media::asJSON(void) {
  nlohmann::json json;

  return json;
}