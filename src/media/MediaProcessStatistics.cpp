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
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    MediaProcessStatistics::container.log.debug(
        {"[MediaProcessStatistics.cpp] RAW OUTPUT: ", buffer.data()});
    result += buffer.data();
    std::cout << " LINE " << buffer.data();
    // std::this_thread::sleep_for(
    //     std::chrono::seconds(1));  // delay for long running processes
  }

  MediaProcessStatistics::container.log.debug(
      {"[MediaProcessStatistics.cpp] OUTPUT: ", result});
  MediaProcessStatistics::parse(result);
}

void MediaProcessStatistics::parse(std::string data) {
  nlohmann::json JSON = nlohmann::json::parse(data);
  Media& media = MediaProcessStatistics::media;
  ProbeResult pr = ProbeResult(JSON);

  assert(pr.videoStreams.size() > 0);

  ProbeResultStreamVideo prsv = pr.videoStreams[0];

  std::istringstream rateStream(pr.videoStreams[0].r_frame_rate);
  int numerator, denominator;
  char slash;
  rateStream >> numerator >> slash >> denominator;

  const auto timeMatch = prsv.tags.DURATION;
  size_t pos = 0;
  int hours, minutes, seconds;
  sscanf(timeMatch.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);
  const int duration = (hours * 60 * 60) + (minutes * 60) + seconds;

  media.file.size = std::stoi(pr.format.size);
  media.video.fps =
      round((static_cast<double>(numerator) / denominator) * 100) / 100;
  media.video.width = prsv.width;
  media.video.height = prsv.height;
  media.video.totalFrames =
      static_cast<int>(std::ceil(duration * media.video.fps));
}