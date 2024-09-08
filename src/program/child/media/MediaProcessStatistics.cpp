#include "MediaProcessStatistics.h"

#include <assert.h>
#include <stdio.h>

#include <array>
#include <cmath>
#include <cstdio>
#include <exception>
#include <iosfwd>
#include <memory>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../../../logging/Log.h"
#include "../../../utils/ListUtils.h"
#include "../../Program.h"
#include "../../settings/enums/Activity.h"
#include "../ffmpeg/ProbeResult.h"
#include "../ffmpeg/ProbeResultStreamVideo.h"
#include "Media.h"
#include "MediaFormat.h"
#include "MediaProcess.h"
#include "../../../utils/RegexUtils.h"

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif
MediaProcessStatistics::MediaProcessStatistics(Media* media)
  : MediaProcess(media) {}

MediaProcessStatistics::~MediaProcessStatistics() {
  MediaProcess::~MediaProcess();
}

void MediaProcessStatistics::start(std::string command) {
  Log::debug({ "[MediaProcessStatistics.cpp] SENDING COMMAND:", command });

  MediaProcessStatistics::status = MediaProcessStatistics::Status::RUNNING;


  std::array<char, 128> buffer;
  std::string result;

  // Open pipe to file
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
    pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  // TODO: this might cause problems in the future

  // Read from pipe
  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) !=
    nullptr) {
    // MediaProcessStatistics::container.log.debug(
    //     {"[MediaProcessStatistics.cpp] RAW OUTPUT: ", buffer.data()});
    result += buffer.data();
    // std::this_thread::sleep_for(
    //     std::chrono::seconds(1));  // delay for long running processes
  }

  // MediaProcessStatistics::container.log.debug(
  //    {"[MediaProcessStatistics.cpp] OUTPUT: ", result});
  MediaProcessStatistics::parse(result);
}

void MediaProcessStatistics::parse(std::string data) {
  try {

    if (RegexUtils::isMatch(data, "not recognized") || RegexUtils::isMatch(data, "unknown command")) {
      Log::debug({ "[MediaProcessStatistics] Could not find ffprobe, failing.", data });
      // TODO: add FAILED_MISSING_FFPROBE
      this->media->setActivity(Activity::FAILED);
      return;
    }

    nlohmann::json JSON = nlohmann::json::parse(data);
    this->media->probeResult = new ProbeResult(JSON);

    //TODO: validate that file exists, assert fails when file missing
    assert(this->media->probeResult->videoStreams.size() > 0);

    Log::debug({ "[MediaProcessStatistics.cpp] VIDEO STREAMS: ",
                std::to_string(this->media->probeResult->videoStreams.size()) });

    ProbeResultStreamVideo prsv = this->media->probeResult->videoStreams[0];

    std::istringstream rateStream(
      this->media->probeResult->videoStreams[0].r_frame_rate);

    int numerator, denominator;
    char slash;
    rateStream >> numerator >> slash >> denominator;

    int hours;
    int minutes;
    int seconds;
    int duration;

    if (!prsv.tags.DURATION.empty()) {
      // TODO: calc duration??
      std::vector<std::string> timeParts =
        ListUtils::splitv(prsv.tags.DURATION, std::string(":"));

      hours = std::stoi(timeParts[0]);
      minutes = std::stoi(timeParts[1]);
      seconds = std::stoi(timeParts[2]);
      duration = (hours * 60 * 60) + (minutes * 60) + seconds;
    }
    else {
      Log::debug({ "[MediaProcessStatistics.cpp] DURATION NOT FOUND" });
      Log::debug(
        { "[MediaProcessStatistics.cpp] Obtaining duration from format. This "
         "could be inaccurate." });

      duration = (int)std::stof(this->media->probeResult->format.duration);
    }

    this->media->file->size =
      std::stoull(this->media->probeResult->format.size);
    this->media->video->fps =
      round((static_cast<float>(numerator) / denominator) * 100) / 100;
    this->media->video->width = prsv.width;
    this->media->video->height = prsv.height;
    this->media->video->totalFrames =
      static_cast<int>(std::ceil(duration * this->media->video->fps));

    assert(!Program::settings->argumentParser->quality.get().name.empty());

    MediaFormat format = Program::settings->argumentParser->quality;

    this->media->video->convertedWidth = std::to_string(format.width);
    this->media->video->convertedHeight = std::to_string(format.getResolution(
      this->media->video->width, this->media->video->height, format.width));
    this->media->video->convertedResolution =
      this->media->video->convertedWidth + ":" +
      this->media->video->convertedHeight;
    this->media->video->crf = format.crf;
  }
  catch (const std::exception& e) {
    Log::debug({ "[MediaProcessStatistics.cpp] ERROR: ", e.what() });
    this->media->setActivity(Activity::FAILED_JSON_PARSE);
    MediaProcessStatistics::status = MediaProcess::Status::_ERROR;
    return;
  }
}