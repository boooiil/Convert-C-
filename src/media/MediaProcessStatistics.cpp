#include "MediaProcessStatistics.h"

#include <array>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "../ffmpeg/ProbeResult.h"
#include "../ffmpeg/ProbeResultStreamVideo.h"
#include "../media/MediaDefinedFormat.h"
#include "../utils/ListUtils.h"
#include "../utils/RegexUtils.h"

#ifdef _WIN32
#include <cstdio>
#define popen _popen
#define pclose _pclose
#else
#include <cstdio>
#endif

MediaProcessStatistics::MediaProcessStatistics(Container* container,
                                               Media* media)
    : MediaProcess(container, media) {}

MediaProcessStatistics::~MediaProcessStatistics() {
  MediaProcess::~MediaProcess();
}

void MediaProcessStatistics::start(std::string command) {
  Log::debug({"[MediaProcessStatistics.cpp] SENDING COMMAND:", command});

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
    nlohmann::json JSON = nlohmann::json::parse(data);
    this->media->probeResult = new ProbeResult(JSON);

    assert(this->media->probeResult->videoStreams.size() > 0);

    Log::debug({"[MediaProcessStatistics.cpp] VIDEO STREAMS: ",
                std::to_string(this->media->probeResult->videoStreams.size())});

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
    } else {
      Log::debug({"[MediaProcessStatistics.cpp] DURATION NOT FOUND"});
      Log::debug(
          {"[MediaProcessStatistics.cpp] Obtaining duration from format. This "
           "could be inaccurate."});

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

    assert(!this->container->userSettings.quality.get().name.empty());

    MediaFormat format = container->userSettings.quality;

    this->media->video->convertedWidth = std::to_string(format.width);
    this->media->video->convertedHeight = std::to_string(format.getResolution(
        this->media->video->width, this->media->video->height, format.width));
    this->media->video->convertedResolution =
        this->media->video->convertedWidth + ":" +
        this->media->video->convertedHeight;
    this->media->video->crf = format.crf;
  } catch (const std::exception& e) {
    Log::debug({"[MediaProcessStatistics.cpp] ERROR: ", e.what()});
    this->media->setActivity(Activity::FAILED_JSON_PARSE);
    MediaProcessStatistics::status = MediaProcess::Status::_ERROR;
    return;
  }
}