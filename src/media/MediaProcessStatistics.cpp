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
#include "../utils/RegexUtils.h"

#ifdef _WIN32
#include <cstdio>
#define popen _popen
#define pclose _pclose
#else
#include <cstdio>
#endif

MediaProcessStatistics::MediaProcessStatistics(Container& container,
                                               Media& media)
    : MediaProcess(container, media) {}

MediaProcessStatistics::~MediaProcessStatistics() {
  MediaProcess::~MediaProcess();
}

/**
 * @brief Start the process.
 *
 * @param command The command to execute.
 */
void MediaProcessStatistics::start(std::string command) {
  MediaProcessStatistics::container.log.debug(
      {"[MediaProcessStatistics.cpp] SENDING COMMAND:", command});

  MediaProcessStatistics::status = MediaProcessStatistics::Status::RUNNING;

  std::array<char, 128> buffer;
  std::string result;

  // Open pipe to file
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

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
  nlohmann::json JSON = nlohmann::json::parse(data);
  Container& container = MediaProcessStatistics::container;
  Media& media = MediaProcessStatistics::media;
  ProbeResult pr = ProbeResult(JSON);

  assert(pr.videoStreams.size() > 0);

  ProbeResultStreamVideo prsv = pr.videoStreams[0];

  std::istringstream rateStream(pr.videoStreams[0].r_frame_rate);
  int numerator, denominator;
  char slash;
  rateStream >> numerator >> slash >> denominator;

  // TODO: calc duration??
  const auto timeMatch = prsv.tags.DURATION;
  size_t pos = 0;

  int duration = 0;

  media.file.size = std::stoi(pr.format.size);
  media.video.fps =
      round((static_cast<float>(numerator) / denominator) * 100) / 100;
  media.video.width = prsv.width;
  media.video.height = prsv.height;
  media.video.totalFrames =
      static_cast<int>(std::ceil(duration * media.video.fps));

  assert(RegexUtils::isMatch(container.appEncodingDecision.quality, "720p"));

  MediaFormat format =
      MediaDefinedFormat::formats[container.appEncodingDecision.quality];

  media.video.convertedWidth = std::to_string(format.width);
  media.video.convertedHeight = std::to_string(format.getResolution(
      media.video.width, media.video.height, format.width));
  media.video.convertedResolution =
      media.video.convertedWidth + ":" + media.video.convertedHeight;
  media.video.crf = format.crf;
}