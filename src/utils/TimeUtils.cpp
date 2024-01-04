#include "TimeUtils.h"

#include <chrono>
#include <cmath>

long TimeUtils::getTime() { return 0; };

long TimeUtils::getEpoch() {
  auto currentTime = std::chrono::system_clock::now();

  // Convert the time point to time_t (seconds since epoch)
  std::time_t epochTime = std::chrono::system_clock::to_time_t(currentTime);

  // Using long to store epoch time
  long epochTimeLong = static_cast<long>(epochTime);

  return epochTimeLong;
};

std::string TimeUtils::durationFormat(long ms) {
  std::string duration("");

  long s = floor(ms / 1000);
  long m = 0;
  long h = 0;

  // get minutes and subtract from seconds
  m = floor(s / 60);
  s -= m * 60;

  // get hours and subtract from minutes
  h = floor(m / 60);
  m -= h * 60;

  if (h > 0) {
    if (h < 10) {
      duration += '0' + h + ':';
    } else if (h > 0) {
      duration += std::to_string(h) + ':';
    } else {
      duration += "00:";
    }
  }
  if (m > 0 || h) {
    if (m < 10) {
      duration += '0' + m + ':';
    } else if (m > 0) {
      duration += std::to_string(m) + ':';
    } else {
      duration += "00:";
    }
  }
  if (s > 0 || h || m) {
    if (s < 10) {
      duration += '0' + s;
    } else {
      duration += std::to_string(s);
    }
  }

  return duration;
};

std::string TimeUtils::dateFormat(long epoch) {
  // Convert the time point to time_t (seconds since epoch)
  std::time_t epochTime = epoch;

  // Convert to local time
  std::tm *localTime = std::localtime(&epochTime);

  // Format the time as a string
  char timeString[80];
  std::strftime(timeString, 80, "%H:%M:%S %Y-%m-%d", localTime);

  return std::string(timeString);
};

std::string TimeUtils::timeFormat(long epoch) {
  // Convert the time point to time_t (seconds since epoch)
  std::time_t epochTime = epoch;

  // Convert to local time
  std::tm *localTime = std::localtime(&epochTime);

  // Format the time as a string
  char timeString[80];
  std::strftime(timeString, 80, "%H:%M:%S-%p", localTime);

  return std::string(timeString);
};