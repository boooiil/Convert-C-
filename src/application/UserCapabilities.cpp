#include "UserCapabilities.h"

#include <array>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "../logging/Log.h"
#include "../utils/RegexUtils.h"

#ifdef _WIN32
#include <cstdio>
#define popen _popen
#define pclose _pclose
#else
#include <cstdio>
#endif

UserCapabilities::UserCapabilities()
    : platform(Platform::UNKNOWN), GPU_Provider("") {}
UserCapabilities::~UserCapabilities() {}

void UserCapabilities::findHardwareDetails() {
#ifdef _WIN32
  platform = Platform::WINDOWS;

  std::array<char, 128> buffer;
  std::string result;

  // Open pipe to file
  std::unique_ptr<FILE, decltype(&pclose)> pipe(
      popen("wmic path win32_VideoController get name", "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  // Read from pipe
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  if (RegexUtils::isMatch(result, "nvidia", std::regex_constants::icase)) {
    GPU_Provider = "nvidia";
  } else if (RegexUtils::isMatch(result, "intel",
                                 std::regex_constants::icase)) {
    GPU_Provider = "intel";
  } else if (RegexUtils::isMatch(result, "amd", std::regex_constants::icase)) {
    GPU_Provider = "amd";
  } else {
    GPU_Provider = "unknown";
  }
#elif __linux__
  platform = Platform::LINUX;

  std::array<char, 128> buffer;
  std::string result;

  // Open pipe to file
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("lspci | grep VGA", "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  // Read from pipe
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  if (RegexUtils::isMatch(result, "nvidia", std::regex_constants::icase)) {
    GPU_Provider = "nvidia";
  } else if (RegexUtils::isMatch(result, "intel",
                                 std::regex_constants::icase)) {
    GPU_Provider = "intel";
  } else if (RegexUtils::isMatch(result, "amd", std::regex_constants::icase)) {
    GPU_Provider = "amd";
  } else {
    GPU_Provider = "unknown";
  }

  Log::debug({"[UserCapabilities.cpp] GPU Provider:", GPU_Provider});

#else
  throw std::runtime_error("Unsupported platform!");
#endif

  Log::debug(
      {"[UserCapabilities.cpp] Platform:", Platform::getValue(platform)});

  Log::debug({"[UserCapabilities.cpp] GPU Provider:", GPU_Provider});

  if (GPU_Provider == "nvidia") {
    supportedEncoders.push_back(Encoders::AV1_NVENC);
    supportedEncoders.push_back(Encoders::H264_NVENC);
    supportedEncoders.push_back(Encoders::HEVC_NVENC);

    supportedDecoders.push_back(Decoders::AV1_CUVID);
    supportedDecoders.push_back(Decoders::H264_CUVID);
    supportedDecoders.push_back(Decoders::HEVC_CUVID);
  } else if (GPU_Provider == "intel") {
    supportedEncoders.push_back(Encoders::AV1_QSV);
    supportedEncoders.push_back(Encoders::H264_QSV);
    supportedEncoders.push_back(Encoders::HEVC_QSV);

    supportedDecoders.push_back(Decoders::AV1_QSV);
    supportedDecoders.push_back(Decoders::H264_QSV);
    supportedDecoders.push_back(Decoders::HEVC_QSV);
  } else if (GPU_Provider == "amd") {
    supportedEncoders.push_back(Encoders::AV1_AMF);
    supportedEncoders.push_back(Encoders::H264_AMF);
    supportedEncoders.push_back(Encoders::HEVC_AMF);
  }

  supportedEncoders.push_back(Encoders::AV1);
  supportedEncoders.push_back(Encoders::H264);
  supportedEncoders.push_back(Encoders::HEVC);

  for (Encoders::Codec encoder : supportedEncoders) {
    Log::debug({"[UserCapabilities.cpp] Supported Encoder:",
                Encoders::getValue(encoder)});
  }

  for (Decoders::Codec decoder : supportedDecoders) {
    Log::debug({"[UserCapabilities.cpp] Supported Decoder:",
                Decoders::getValue(decoder)});
  }
}