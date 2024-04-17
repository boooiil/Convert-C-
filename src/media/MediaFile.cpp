#include "MediaFile.h"

#include <regex>

#include "../application/Ticker.h"
#include "../logging/Log.h"
#include "../utils/ListUtils.h"
#include "../utils/RegexUtils.h"
#include "../utils/StringUtils.h"

MediaFile::MediaFile()
    : modifiedFileName(""),
      modifiedFileNameExt(""),
      conversionName(""),
      conversionPath(""),
      renamePath(""),
      episode(""),
      series(""),
      originalFileName(""),
      originalFullPath(""),
      cwd(""),
      ext(""),
      number(0),
      size(0),
      newSize(0),
      validationSize(0),
      quality(0),
      season(0) {}

MediaFile::MediaFile(std::string name, std::string path)
    : modifiedFileName(""),
      modifiedFileNameExt(""),
      conversionName(""),
      conversionPath(""),
      renamePath(""),
      episode(""),
      series(""),
      originalFileName(name),
      originalFullPath(""),
      cwd(path),
      ext(""),
      number(0),
      size(0),
      newSize(0),
      validationSize(0),
      quality(0),
      season(0) {}

MediaFile::~MediaFile() {
  Log::debug({"[MediaFile] Deconstructing MediaFile"});
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

void MediaFile::rename() {
  // pattern for matching media names
  // ex: The.Big.Bang.Theory.S01E01.720p.HDTV.ReEnc-Max.mkv
  // ex: The Big Bang Theory - S01E01 - Pilot.mkv
  // ex: The Big Bang Theory - 1x01 - Pilot.mkv
  std::string mediaPattern =
      R"((.+?)(?:[-\. ]+)(season.?\d{1,}|s\d{1,}).?((?:E|X)[0-9]{2}(?:-(?:E|X)[0-9]{2}|(?:E|X)[0-9]{2})*(?:-(?:E|X)[0-9]{2})?))";

  // if the media name matches the media pattern
  if (RegexUtils::isMatch(this->originalFileName, mediaPattern,
                          std::regex::icase)) {
    Log::debug({"[Media.cpp] Matched media name: ", this->originalFileName});
    // get all matches of the media name
    std::vector<std::string> media_matches = RegexUtils::getAllMatches(
        this->originalFileName, mediaPattern, std::regex::icase);

    this->resolvePath(this->originalFileName, this->cwd);
    this->resolveExtension(this->originalFileName);

    this->resolveSeries(media_matches[0]);
    this->resolveSeason(media_matches[1]);
    this->resolveEpisode(media_matches[2]);

    this->resolveQuality(this->originalFileName);

    this->resolveModifiedFileName(
        this->series, std::to_string(this->season), this->episode,
        Ticker::container->userSettings.quality.get().name);
    this->resolveModifiedFileNameExt(this->modifiedFileName, this->ext);

    this->resolveRenamePath(this->modifiedFileName, this->ext, this->cwd);

    this->resolveConversionName(this->modifiedFileName, this->ext);
    this->resolveConversionPath(this->conversionName, this->series,
                                std::to_string(this->season), this->cwd);

    Log::debug({"[Media.cpp] Original file:", this->originalFileName});
    Log::debug({"[Media.cpp] Renamed file:", this->conversionName});
  } else {
    // TODO: finish
    Log::debug(
        {"[Media.cpp] Could not match media name: ", this->originalFileName});

    this->resolvePath(this->originalFileName, this->cwd);
    this->resolveExtension(this->originalFileName);
    this->resolveQuality(this->originalFileName);

    this->modifiedFileName =
        StringUtils::replaceAll(this->originalFileName, this->ext, "");
    this->modifiedFileNameExt = this->modifiedFileName + ".mp4";
    this->conversionName = this->modifiedFileNameExt;
    this->conversionPath = this->cwd + "/" + this->conversionName;
  }
}
// if the pattern doesnt match, the mod file name is the same as the original

void MediaFile::resolvePath(std::string original_filename, std::string cwd) {
  this->originalFullPath = cwd + "/" + original_filename;
}

void MediaFile::resolveExtension(std::string original_filename) {
  std::string ext = RegexUtils::getFirstMatch(
      original_filename, R"((\.mkv|\.avi|\.srt|\.idx|\.sub))",
      std::regex::icase);

  if (ext != "") {
    this->ext = ext;
  } else {
    throw std::runtime_error("Could not find extension for file: " +
                             original_filename);
  }
}

void MediaFile::resolveSeries(std::string series_match) {
  if (series_match == "") {
    throw std::runtime_error("Could not find series name for file: " +
                             this->originalFullPath);
  }

  this->series = StringUtils::replaceAll(series_match, ".", " ");
}

// should be a match of
// season ## || s##
// resolves to an integer

void MediaFile::resolveSeason(std::string season_match) {
  if (season_match == "") {
    throw std::runtime_error("Could not find season number for file: " +
                             this->originalFullPath);
  }

  this->season = std::stoi(StringUtils::replaceAll(
      season_match, std::regex(R"(season|s)", std::regex::icase), ""));
}

// should be a match of
// e## || x##
// e##-e## || x##-x##

void MediaFile::resolveEpisode(std::string episode_match) {
  if (episode_match == "") {
    throw std::runtime_error("Could not find episode number for file: " +
                             this->originalFullPath);
  }

  this->episode =
      StringUtils::replaceAll(episode_match, std::regex(R"([XxE])"), "e");
}

void MediaFile::resolveQuality(std::string original_filename) {
  std::string quality_match = RegexUtils::getFirstMatch(
      original_filename, R"((1080p|720p|480p))", std::regex::icase);

  if (quality_match == "") {
    Log::debug({"[Media.cpp] Could not find quality for file: ",
                this->originalFullPath});
  } else {
    this->quality = std::stoi(StringUtils::replaceAll(quality_match, "p", ""));
  }
}

void MediaFile::resolveModifiedFileName(std::string series, std::string season,
                                        std::string episode,
                                        std::string quality) {
  if (quality == "") {
    this->modifiedFileName =
        StringUtils::replaceAll(series, ".", "") + " - s" + season + episode;
  } else {
    this->modifiedFileName =
        series + " - s" + season + episode + " [" + quality + "]";
  }
}

// set renamed media name with extension
// it will also need to account for mkv and avi files
// if mkv || avi, make ext mkv
// else make original ext

void MediaFile::resolveModifiedFileNameExt(std::string modified_filename,
                                           std::string ext) {
  if (ext == ".mkv" || ext == ".avi") {
    this->modifiedFileNameExt = modified_filename + ".mkv";
  } else {
    this->modifiedFileNameExt = modified_filename + ext;
  }
}

// path to the renamed file
// (cwd)/(modified_filename)
// ie: /path/to/renamed/file/some season.mkv

void MediaFile::resolveRenamePath(std::string modified_filename,
                                  std::string ext, std::string cwd) {
  this->renamePath = cwd + "/" + modified_filename + ext;
}

void MediaFile::resolveConversionName(std::string modified_filename,
                                      std::string extension) {
  this->conversionName = modified_filename + extension;
}

// path to the converted file
// (cwd)/(series name) (series number)/(conversion_name)

void MediaFile::resolveConversionPath(std::string conversion_filename,
                                      std::string series, std::string season,
                                      std::string cwd) {
  this->conversionPath =
      cwd + "/" + series + " Season " + season + "/" + conversion_filename;
}
