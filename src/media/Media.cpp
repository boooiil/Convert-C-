/*********************************************************************
 * @file   Media.cpp
 * @brief  Media class implementation file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#include "Media.h"

#include <regex>
#include <string>

#include "../../logging/Log.h"
#include "../application/Container.h"
#include "../media/MediaDefinedFormat.h"
#include "../utils/ListUtils.h"
#include "../utils/RegexUtils.h"
#include "./MediaProcessConversion.h"
#include "./MediaProcessStatistics.h"
#include "./MediaProcessValidate.h"

Media::Media()
    : started(0),
      ended(0),
      activity(Activity::WAITING),
      file(new MediaFile()),
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
      video(new MediaVideoProperties()),
      working(new MediaWorkingProperties()) {}

Media::~Media() {
  Log::debug(
      {"[Media.cpp] Deconstructing media: ", this->file->originalFileName});

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

void Media::setActivity(Activity::ActivityType activity) {
  Media::activity = activity;
}

void Media::doStatistics(Container* container) {
  this->setActivity(Activity::STATISTICS);

  Log::debug(
      {"[Media.cpp] Starting statistics for: ", this->file->originalFileName});

  MediaProcessStatistics statistics(container, this);
  statistics.start(
      "ffprobe -v quiet -print_format json -show_format "
      "-show_streams \"" +
      this->file->originalFullPath + "\"");

  if (this->hasFailed()) {
    return;
  }

  this->setActivity(Activity::WAITING_CONVERT);
}
void Media::doConversion(Container* container) {
  this->setActivity(Activity::CONVERT);

  Log::debug(
      {"[Media.cpp] Starting conversion for: ", this->file->originalFileName});

  MediaProcessConversion conversion(container, this);

  conversion.start("ffmpeg " + ListUtils::join(Media::ffmpegArguments, " "));

  if (this->hasFailed()) {
    return;
  }

  this->setActivity(Activity::WAITING_VALIDATE);
}
void Media::doValidation(Container* container) {
  this->setActivity(Activity::VALIDATE);

  Log::debug(
      {"[Media.cpp] Starting validation for: ", this->file->originalFileName});

  MediaProcessValidate validate(container, this);
  validate.start("ffmpeg -v quiet -stats -i \"" + this->file->conversionPath +
                 "\" -f null -");

  if (this->hasFailed()) {
    return;
  }

  this->setActivity(Activity::FINISHED);
}

void Media::buildFFmpegArguments(Container* container, bool isValidate) {
  MediaFormat format = container->userSettings.quality;

  this->ffmpegArguments.clear();

  this->ffmpegArguments.push_back("-v error -stats");

  if (container->userSettings.useHardwareDecode) {
    if (container->programSettings.runningHWAccel != HWAccelerators::NONE) {
      this->ffmpegArguments.push_back(
          "-hwaccel " +
          HWAccelerators::getValue(container->programSettings.runningHWAccel));
    }
  }

  this->ffmpegArguments.push_back("-i \"" + this->file->originalFullPath +
                                  "\"");

  this->ffmpegArguments.push_back("-map 0:v:0");

  if (!container->userSettings.audioStreams.get().empty()) {
    for (const int stream : container->userSettings.audioStreams.get()) {
      this->ffmpegArguments.push_back("-map 0:a:" + stream);
    }
  } else {
    this->ffmpegArguments.push_back("-map 0:a?");
  }

  this->ffmpegArguments.push_back("-map 0:s?");
  this->ffmpegArguments.push_back("-map 0:t?");

  this->ffmpegArguments.push_back(
      "-c:v " + Encoders::getValue(container->programSettings.runningEncoder));
  this->ffmpegArguments.push_back("-c:t copy");
  this->ffmpegArguments.push_back("-c:a copy");

  this->ffmpegArguments.push_back("-preset slow");

  this->ffmpegArguments.push_back("-level 4.1");

  if (container->userSettings.useBitrate) {
    this->ffmpegArguments.push_back("-b:v " + std::to_string(format.bitrate) +
                                    "M");
    this->ffmpegArguments.push_back("-bufsize " +
                                    std::to_string(format.bitrate * 2) + "M");
    this->ffmpegArguments.push_back("-maxrate " +
                                    std::to_string(format.max * 2) + "M");
    this->ffmpegArguments.push_back("-minrate " +
                                    std::to_string(format.min * 2) + "M");
  } else if (container->userSettings.useConstrain) {
    this->ffmpegArguments.push_back("-crf " + std::to_string(format.crf));
    this->ffmpegArguments.push_back("-bufsize " +
                                    std::to_string(format.bitrate * 2) + "M");
    this->ffmpegArguments.push_back("-maxrate " +
                                    std::to_string(format.max * 2) + "M");
  } else {
    this->ffmpegArguments.push_back("-crf " + std::to_string(format.crf));
  }

  if (container->userSettings.crop) {
    this->ffmpegArguments.push_back(
        "-vf scale=" + this->video->convertedResolution +
        ":flags=lanczos,crop=" + format.crop);

  }

  else
    this->ffmpegArguments.push_back(
        "-vf scale=" + this->video->convertedResolution + ":flags=lanczos");

  if (!container->userSettings.startBeginning.get().empty()) {
    this->ffmpegArguments.push_back(
        "-ss " + container->userSettings.startBeginning.get());
  }

  if (!container->userSettings.trim.get().empty()) {
    this->ffmpegArguments.push_back("-ss " +
                                    container->userSettings.trim.get()[0]);
    this->ffmpegArguments.push_back("-to " +
                                    container->userSettings.trim.get()[1]);
  }

  /** TODO: flesh out later */
  // if (this.video.subtitle_provider) {

  //     if (this.video.subtitle_provider === "mov")
  //     this.ffmpeg_argument.push("-c:s mov_text") else
  //     this.ffmpeg_argument.push("-c:s copy")

  // }

  this->ffmpegArguments.push_back("-c:s copy");

  if (container->userSettings.tune != Tunes::DEFAULT) {
    this->ffmpegArguments.push_back(
        "-tune " + Tunes::getValue(container->userSettings.tune));
  }

  this->ffmpegArguments.push_back("\"" + this->file->conversionPath + "\"");

  if (isValidate || container->userSettings.overwrite)
    this->ffmpegArguments.push_back("-y");
  else {
    this->ffmpegArguments.push_back("-n");
  }

  Log::debug(
      {"FFMPEG ARGUMENTS: ", ListUtils::join(this->ffmpegArguments, " ")});
}
