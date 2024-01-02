#include "Media.h"

#include <regex>
#include <string>

#include "../application/Container.h"
#include "../utils/ListUtils.h"
#include "../utils/RegexUtils.h"
#include "../utils/StringUtils.h"
#include "./MediaProcessConversion.h"
#include "./MediaProcessStatistics.h"

Media::Media() : started(0), ended(0) {}
Media::Media(std::string name, std::string path) : started(0), ended(0) {
  Media::name = name;
  Media::path = path;
}

Media::~Media() {}

/**
 * @brief Check if the media is currently processing.
 *
 * @return true Media is processing.
 * @return false Media is not processing.
 */
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

  Media::activity = Activity::WAITING_CONVERT;

  // TODO: implement in a way where this isn't necessary
  // container.converting[Media::name] = *this;
}
void Media::doConversion(Container& container) {
  Media::activity = Activity::CONVERT;

  container.log.debug({"[Media.cpp] Starting conversion for: ", Media::name});

  MediaProcessConversion conversion(container, *this);
  conversion.start("ffmpeg -v quiet -stats -i \"" + Media::file.path + "\" " +
                   ListUtils::join(Media::ffmpegArguments, " ") + "\"" +
                   Media::file.conversionPath + "\" -y");

  // TODO: implement this
  Media::activity = Activity::WAITING_VALIDATE;

  // TODO: implement in a way where this isn't necessary
  // container.converting[Media::name] = *this;
}
void Media::doValidation(Container& container) {
  Media::activity = Activity::VALIDATE;

  container.log.debug({"[Media.cpp] Starting validation for: ", Media::name});

  // TODO: implement this
  Media::activity = Activity::FINISHED;

  // TODO: implement in a way where this isn't necessary
  // container.converting[Media::name] = *this;
}

/**
 * @brief Build the FFMpeg arguments for the media.
 *
 * @param container The container to use for the arguments.
 * @param isValidate True if the arguments are for validation.
 */
void Media::buildFFmpegArguments(Container& container, bool isValidate) {}
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

// original file path
void Media::resolvePath(std::string original_filename, std::string cwd) {
  Media::file.path = cwd + "/" + original_filename;
}

// original file extension
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

// should be the series name
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

// should be a match of
// 1080p || 720p || 480p
// resolves to an integer
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

// set renamed media name without extension
// this will be the season name without periods
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
