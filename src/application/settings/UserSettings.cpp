#include "./UserSettings.h"

#include <array>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "../../logging/Log.h"
#include "../../media/MediaDefinedFormat.h"
#include "../../utils/RegexUtils.h"

UserSettings::UserSettings(void)
    : validate(false),
      platform(Platform::OPERATING_SYSTEM::UNKNOWN),
      GPU_Provider(GPUProviders::Provider::UNKNOWN){};

UserSettings::~UserSettings(void) {}

void UserSettings::validateSettings() {
  // set hevc as fallback encoder
  if (this->wantedEncoder == Encoders::INVALID) {
    this->wantedEncoder.set(Encoders::HEVC);
  }
  // hevc does not support film tune
  // i'm sure av1 does not as well
  if (UserSettings::tune == Tunes::FILM &&
      Encoders::isHEVC(UserSettings::wantedEncoder)) {
    UserSettings::tune = Tunes::DEFAULT;
  }
}

void UserSettings::findHardwareDetails() {
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
  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) !=
         nullptr) {
    result += buffer.data();
  }

  // nvidia
  if (RegexUtils::isMatch(result, "nvidia", std::regex_constants::icase)) {
    GPU_Provider = GPUProviders::NVIDIA;
  }
  // intel
  else if (RegexUtils::isMatch(result, "intel", std::regex_constants::icase)) {
    GPU_Provider = GPUProviders::INTEL;
  }
  // amd
  else if (RegexUtils::isMatch(result, "amd", std::regex_constants::icase)) {
    GPU_Provider = GPUProviders::AMD;
  }
  // unknown
  else {
    GPU_Provider = GPUProviders::UNKNOWN;
  }
#elif __linux__
  platform = Platform::_LINUX;

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

  // nvidia
  if (RegexUtils::isMatch(result, "nvidia", std::regex_constants::icase)) {
    GPU_Provider = GPUProviders::NVIDIA;
  }
  // intel
  else if (RegexUtils::isMatch(result, "intel", std::regex_constants::icase)) {
    GPU_Provider = GPUProviders::INTEL;
  }
  // amd
  else if (RegexUtils::isMatch(result, "amd", std::regex_constants::icase)) {
    GPU_Provider = GPUProviders::AMD;
  }
  // unknown
  else {
    GPU_Provider = GPUProviders::UNKNOWN;
  }

#else
  throw std::runtime_error("Unsupported platform!");
#endif

  Log::debug(
      {"[UserCapabilities.cpp] Platform:", Platform::getValue(platform)});

  Log::debug({"[UserCapabilities.cpp] GPU Provider:",
              GPUProviders::getValue(GPU_Provider)});

  if (GPU_Provider == GPUProviders::NVIDIA) {
    // set encoders
    supportedEncoders.push_back(Encoders::AV1_NVENC);
    supportedEncoders.push_back(Encoders::H264_NVENC);
    supportedEncoders.push_back(Encoders::HEVC_NVENC);
    // set decoders
    supportedDecoders.push_back(Decoders::AV1_CUVID);
    supportedDecoders.push_back(Decoders::H264_CUVID);
    supportedDecoders.push_back(Decoders::HEVC_CUVID);
    // set hw accel
    supportedHWAccel.push_back(HWAccelerators::NVIDIA);
  } else if (GPU_Provider == GPUProviders::INTEL) {
    // set encoders
    supportedEncoders.push_back(Encoders::AV1_QSV);
    supportedEncoders.push_back(Encoders::H264_QSV);
    supportedEncoders.push_back(Encoders::HEVC_QSV);
    // set decoders
    supportedDecoders.push_back(Decoders::AV1_QSV);
    supportedDecoders.push_back(Decoders::H264_QSV);
    supportedDecoders.push_back(Decoders::HEVC_QSV);
    // set hw accel
    supportedHWAccel.push_back(HWAccelerators::INTEL);
  } else if (GPU_Provider == GPUProviders::AMD) {
    // set encoders
    supportedEncoders.push_back(Encoders::AV1_AMF);
    supportedEncoders.push_back(Encoders::H264_AMF);
    supportedEncoders.push_back(Encoders::HEVC_AMF);
    // set hw accel
    supportedHWAccel.push_back(HWAccelerators::AMD);
  }

  // set software encoders
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