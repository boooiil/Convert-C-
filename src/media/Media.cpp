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

#include "../application/Container.h"
#include "../media/MediaDefinedFormat.h"
#include "../utils/ListUtils.h"
#include "../utils/RegexUtils.h"
#include "../utils/StringUtils.h"
#include "./MediaProcessConversion.h"
#include "./MediaProcessStatistics.h"
#include "./MediaProcessValidate.h"

Media::Media() : started(0), ended(0) {}
Media::Media(std::string name, std::string path) : started(0), ended(0) {
  Media::name = name;
  Media::path = path;
}

Media::~Media() {
  Log::debug({"[Media.cpp] Destroying media: ", Media::name});
}

bool Media::isProcessing() {
  if (activity == Activity::STATISTICS || activity == Activity::CONVERT ||
      activity == Activity::VALIDATE) {
    return true;
  }
  return false;
}

void Media::doStatistics(Container& container) {
  Media::activity = Activity::STATISTICS;

  container.log.debug({"[Media.cpp] Starting statistics for: ", Media::name});

  MediaProcessStatistics statistics(container, *this);
  statistics.start(
      "ffprobe -v quiet -print_format json -show_format "
      "-show_streams \"" +
      Media::file.path + "\"");

  if (RegexUtils::isMatch(Activity::getValue(Media::activity), "failed",
                          std::regex::icase)) {
    return;
  }

  Media::activity = Activity::WAITING_CONVERT;
}
void Media::doConversion(Container& container) {
  Media::activity = Activity::CONVERT;

  container.log.debug({"[Media.cpp] Starting conversion for: ", Media::name});

  MediaProcessConversion conversion(container, *this);

  conversion.start("ffmpeg " + ListUtils::join(Media::ffmpegArguments, " "));

  if (RegexUtils::isMatch(Activity::getValue(Media::activity), "failed",
                          std::regex::icase)) {
    return;
  }

  Media::activity = Activity::WAITING_VALIDATE;
}
void Media::doValidation(Container& container) {
  Media::activity = Activity::VALIDATE;

  container.log.debug({"[Media.cpp] Starting validation for: ", Media::name});

  MediaProcessValidate validate(container, *this);
  validate.start("ffmpeg -v quiet -stats -i \"" + Media::file.conversionPath +
                 "\" -f null -");

  if (RegexUtils::isMatch(Activity::getValue(Media::activity), "failed",
                          std::regex::icase)) {
    return;
  }
  // TODO: implement this
  Media::activity = Activity::FINISHED;
}

void Media::buildFFmpegArguments(Container& container, bool isValidate) {
  MediaFormat format =
      MediaDefinedFormat::formats[container.appEncodingDecision.quality];

  this->ffmpegArguments.clear();

  this->ffmpegArguments.push_back("-v quiet -stats");

  if (container.appEncodingDecision.useHardwareEncode) {
    if (container.userCapabilities.GPU_Provider == "amd") {
      this->ffmpegArguments.push_back("-hwaccel amf");
    } else if (container.userCapabilities.GPU_Provider == "intel") {
      this->ffmpegArguments.push_back("-hwaccel qsv");
    } else if (container.userCapabilities.GPU_Provider == "nvidia") {
      this->ffmpegArguments.push_back("-hwaccel cuda");
    }
  }

  this->ffmpegArguments.push_back("-i \"" + this->file.path + "\"");

  this->ffmpegArguments.push_back("-map 0:v:0");

  if (container.appEncodingDecision.audioStreams.size()) {
    for (const std::string stream :
         container.appEncodingDecision.audioStreams) {
      this->ffmpegArguments.push_back("-map 0:a:" + stream);
    }
  } else {
    this->ffmpegArguments.push_back("-map 0:a?");
  }

  this->ffmpegArguments.push_back("-map 0:s?");
  this->ffmpegArguments.push_back("-map 0:t?");

  this->ffmpegArguments.push_back("-c:v " +
                                  container.appEncodingDecision.runningEncoder);
  this->ffmpegArguments.push_back("-c:t copy");
  this->ffmpegArguments.push_back("-c:a copy");

  this->ffmpegArguments.push_back("-preset slow");

  this->ffmpegArguments.push_back("-level 4.1");

  if (container.appEncodingDecision.useBitrate) {
    this->ffmpegArguments.push_back("-b:v " + std::to_string(format.bitrate) +
                                    "M");
    this->ffmpegArguments.push_back("-bufsize " +
                                    std::to_string(format.bitrate * 2) + "M");
    this->ffmpegArguments.push_back("-maxrate " +
                                    std::to_string(format.max * 2) + "M");
    this->ffmpegArguments.push_back("-minrate " +
                                    std::to_string(format.min * 2) + "M");
  } else if (container.appEncodingDecision.useConstrain) {
    this->ffmpegArguments.push_back("-crf " + std::to_string(format.crf));
    this->ffmpegArguments.push_back("-bufsize " +
                                    std::to_string(format.bitrate * 2) + "M");
    this->ffmpegArguments.push_back("-maxrate " +
                                    std::to_string(format.max * 2) + "M");
  } else {
    this->ffmpegArguments.push_back("-crf " + std::to_string(format.crf));
  }

  if (container.appEncodingDecision.crop) {
    this->ffmpegArguments.push_back(
        "-vf scale=" + this->video.convertedResolution +
        ":flags=lanczos,crop=" + format.crop);

  }

  else
    this->ffmpegArguments.push_back(
        "-vf scale=" + this->video.convertedResolution + ":flags=lanczos");

  if (container.appEncodingDecision.startBeginning != "") {
    this->ffmpegArguments.push_back(
        "-ss " + container.appEncodingDecision.startBeginning);
  }

  if (container.appEncodingDecision.trim != "") {
    std::vector<std::string> trim =
        ListUtils::splitv(container.appEncodingDecision.trim, ",");

    this->ffmpegArguments.push_back("-ss " + trim[0]);
    this->ffmpegArguments.push_back("-to " + trim[1]);
  }

  /** TODO: flesh out later */
  // if (this.video.subtitle_provider) {

  //     if (this.video.subtitle_provider === "mov")
  //     this.ffmpeg_argument.push("-c:s mov_text") else
  //     this.ffmpeg_argument.push("-c:s copy")

  // }

  this->ffmpegArguments.push_back("-c:s copy");

  if (container.appEncodingDecision.tune != "") {
    this->ffmpegArguments.push_back("-tune " +
                                    container.appEncodingDecision.tune);
  }

  this->ffmpegArguments.push_back("\"" + this->file.conversionPath + "\"");

  if (isValidate || container.appEncodingDecision.overwrite)
    this->ffmpegArguments.push_back("-y");
  else {
    this->ffmpegArguments.push_back("-n");
  }

  container.log.debug(
      {"FFMPEG ARGUMENTS: ", ListUtils::join(this->ffmpegArguments, " ")});
}

void Media::rename(Container& container) {
  Media::file.path = Media::path + "/" + Media::name;

  // pattern for matching media names
  // ex: The.Big.Bang.Theory.S01E01.720p.HDTV.ReEnc-Max.mkv
  // ex: The Big Bang Theory - S01E01 - Pilot.mkv
  // ex: The Big Bang Theory - 1x01 - Pilot.mkv
  std::string mediaPattern =
      R"((.+?)(?:[-\. ]+)(season.?\d{1,}|s\d{1,}).?((?:E|X)[0-9]{2}(?:-(?:E|X)[0-9]{2}|(?:E|X)[0-9]{2})*(?:-(?:E|X)[0-9]{2})?))";

  // if the media name matches the media pattern
  if (RegexUtils::isMatch(Media::name, mediaPattern, std::regex::icase)) {
    // get all matches of the media name
    std::vector<std::string> media_matches =
        RegexUtils::getAllMatches(Media::name, mediaPattern, std::regex::icase);

    Media::resolvePath(Media::name, Media::path);
    Media::resolveExtension(Media::name);

    Media::resolveSeries(media_matches[0]);
    Media::resolveSeason(media_matches[1]);
    Media::resolveEpisode(media_matches[2]);

    Media::resolveQuality(Media::name);

    Media::resolveModifiedFileName(
        Media::file.series, std::to_string(Media::file.season),
        Media::file.episode, container.appEncodingDecision.quality);
    Media::resolveModifiedFileNameExt(Media::file.modifiedFileName,
                                      Media::file.ext);

    Media::resolveRenamePath(Media::file.modifiedFileName, Media::file.ext,
                             Media::path);

    Media::resolveConversionName(Media::file.modifiedFileName, Media::file.ext);
    Media::resolveConversionPath(Media::file.conversionName, Media::file.series,
                                 std::to_string(Media::file.season),
                                 Media::path);

    container.log.debug({"[Media.cpp] Original file:", Media::name});
    container.log.debug(
        {"[Media.cpp] Renamed file:", Media::file.conversionName});
  } else {
    // TODO: finish
  }
}

/**
 * Checklist:
 *
 *   Make these all separate private functions
 *
 *   [x] - Path (full path with file name)
 *   [x] - Extension
 *   [x] - Modified file name
 *   [x] - Modified file name ext
 *   [x] - Conversion name
 *   [x] - Conversion path
 *   [x] - Rename path
 *   [] - Episode (episodes are matching e00- instead of e00)
 *   [x] - Series
 *   [x] - Quality
 *   [x] - Season
 */

// if the pattern doesnt match, the mod file name is the same as the original

void Media::resolvePath(std::string original_filename, std::string cwd) {
  Media::file.path = cwd + "/" + original_filename;
}

void Media::resolveExtension(std::string original_filename) {
  std::string ext = RegexUtils::getFirstMatch(
      original_filename, R"((\.mkv|\.avi|\.srt|\.idx|\.sub))",
      std::regex::icase);

  if (ext != "") {
    Media::file.ext = ext;
  } else {
    throw std::runtime_error("Could not find extension for file: " +
                             original_filename);
  }
}

void Media::resolveSeries(std::string series_match) {
  if (series_match == "") {
    throw std::runtime_error("Could not find series name for file: " +
                             Media::file.path);
  }

  Media::file.series = StringUtils::replaceAll(series_match, ".", " ");
}

// should be a match of
// season ## || s##
// resolves to an integer

void Media::resolveSeason(std::string season_match) {
  if (season_match == "") {
    throw std::runtime_error("Could not find season number for file: " +
                             Media::file.path);
  }

  Media::file.season = std::stoi(StringUtils::replaceAll(
      season_match, std::regex(R"(season|s)", std::regex::icase), ""));
}

// should be a match of
// e## || x##
// e##-e## || x##-x##

void Media::resolveEpisode(std::string episode_match) {
  if (episode_match == "") {
    throw std::runtime_error("Could not find episode number for file: " +
                             Media::file.path);
  }

  Media::file.episode =
      StringUtils::replaceAll(episode_match, std::regex(R"([XxE])"), "e");
}

void Media::resolveQuality(std::string original_filename) {
  std::string quality_match = RegexUtils::getFirstMatch(
      original_filename, R"((1080p|720p|480p))", std::regex::icase);

  if (quality_match == "") {
    Log::debug(
        {"[Media.cpp] Could not find quality for file: ", Media::file.path});
  } else {
    Media::file.quality =
        std::stoi(StringUtils::replaceAll(quality_match, "p", ""));
  }
}

void Media::resolveModifiedFileName(std::string series, std::string season,
                                    std::string episode, std::string quality) {
  if (quality == "") {
    Media::file.modifiedFileName =
        StringUtils::replaceAll(series, ".", "") + " - s" + season + episode;
  } else {
    Media::file.modifiedFileName =
        series + " - s" + season + episode + " [" + quality + "]";
  }
}

// set renamed media name with extension
// it will also need to account for mkv and avi files
// if mkv || avi, make ext mkv
// else make original ext

void Media::resolveModifiedFileNameExt(std::string modified_filename,
                                       std::string ext) {
  if (ext == ".mkv" || ext == ".avi") {
    Media::file.modifiedFileNameExt = modified_filename + ".mkv";
  } else {
    Media::file.modifiedFileNameExt = modified_filename + ext;
  }
}

// path to the renamed file
// (cwd)/(modified_filename)
// ie: /path/to/renamed/file/some season.mkv

void Media::resolveRenamePath(std::string modified_filename, std::string ext,
                              std::string cwd) {
  Media::file.renamePath = cwd + "/" + modified_filename + ext;
}

void Media::resolveConversionName(std::string modified_filename,
                                  std::string extension) {
  Media::file.conversionName = modified_filename + extension;
}

// path to the converted file
// (cwd)/(series name) (series number)/(conversion_name)

void Media::resolveConversionPath(std::string conversion_filename,
                                  std::string series, std::string season,
                                  std::string cwd) {
  Media::file.conversionPath =
      cwd + "/" + series + " Season " + season + "/" + conversion_filename;
}
