#include "./ProgramSettings.h"

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#define popen _popen
#define pclose _pclose
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <stdio.h>

#include <array>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>

#include "../../logging/Log.h"
#include "../../utils/RegexUtils.h"
#include "../Program.h"
#include "arguments/ArgumentParser.h"
#include "enums/Encoders.h"
#include "enums/GPUProviders.h"
#include "enums/HWAccelerators.h"
#include "enums/Platform.h"
#include "enums/Tunes.h"

// TODO: fill this out, rm ApplicationEncodingDecision

ProgramSettings::ProgramSettings()
    : runningEncoder(Encoders::Codec::HEVC),
      runningHWAccel(HWAccelerators::Accelerator::NONE) {
  char buff[FILENAME_MAX];

  if (GetCurrentDir(buff, FILENAME_MAX) != nullptr) {
    std::string tempStr = buff;
    ProgramSettings::workingDir = tempStr;
  } else {
    ProgramSettings::workingDir = "";
  }

  ProgramSettings::tuneRegex = {std::regex(R"(film)", std::regex::icase),
                                std::regex(R"(anim)", std::regex::icase),
                                std::regex(R"(grain)", std::regex::icase)};

  ProgramSettings::tuneAssociations = {Tunes::FILM, Tunes::ANIMATION,
                                       Tunes::GRAIN};
};

ProgramSettings::~ProgramSettings(void){};

void ProgramSettings::validateSettings(ArgumentParser argumentParser) {
  // guard against invalid encoder (should be handled in user settings)
  if (argumentParser.wantedEncoder == Encoders::INVALID) {
    this->runningEncoder = Encoders::Codec::HEVC;
  } else {
    this->runningEncoder = argumentParser.wantedEncoder;
  }

  if (!argumentParser.supportedHWAccel.empty()) {
    this->runningHWAccel = argumentParser.supportedHWAccel[0];
  }

  if (Encoders::isAV1(argumentParser.wantedEncoder)) {
    argumentParser.tune = Tunes::DEFAULT;
  }

  // hevc does not support film tune
  // i'm sure av1 does not as well
  if (argumentParser.tune == Tunes::FILM &&
      Encoders::isHEVC(argumentParser.wantedEncoder)) {
    argumentParser.tune = Tunes::DEFAULT;
  }
};

void ProgramSettings::gatherSystemDetails(void) {
  ArgumentParser argumentParser = *Program::settings->argumentParser;

#ifdef _WIN32
  argumentParser.platform = Platform::WINDOWS;

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
    argumentParser.GPU_Provider = GPUProviders::NVIDIA;
  }
  // intel
  else if (RegexUtils::isMatch(result, "intel", std::regex_constants::icase)) {
    argumentParser.GPU_Provider = GPUProviders::INTEL;
  }
  // amd
  else if (RegexUtils::isMatch(result, "amd", std::regex_constants::icase)) {
    argumentParser.GPU_Provider = GPUProviders::AMD;
  }
  // unknown
  else {
    argumentParser.GPU_Provider = GPUProviders::UNKNOWN;
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
    argumentParser.GPU_Provider = GPUProviders::NVIDIA;
  }
  // intel
  else if (RegexUtils::isMatch(result, "intel", std::regex_constants::icase)) {
    argumentParser.GPU_Provider = GPUProviders::INTEL;
  }
  // amd
  else if (RegexUtils::isMatch(result, "amd", std::regex_constants::icase)) {
    argumentParser.GPU_Provider = GPUProviders::AMD;
  }
  // unknown
  else {
    argumentParser.GPU_Provider = GPUProviders::UNKNOWN;
  }

#else
  throw std::runtime_error("Unsupported platform!");
#endif

  Log::debug({"[UserSettings.cpp] Platform:",
              Platform::getValue(argumentParser.platform)});

  Log::debug({"[UserSettings.cpp] GPU Provider:",
              GPUProviders::getValue(argumentParser.GPU_Provider)});

  if (argumentParser.GPU_Provider == GPUProviders::NVIDIA) {
    // set encoders
    supportedEncoders.push_back(Encoders::AV1_NVENC);
    supportedEncoders.push_back(Encoders::H264_NVENC);
    supportedEncoders.push_back(Encoders::HEVC_NVENC);
    // set decoders
    // supportedDecoders.push_back(Decoders::AV1_CUVID);
    // supportedDecoders.push_back(Decoders::H264_CUVID);
    // supportedDecoders.push_back(Decoders::HEVC_CUVID);
    // set hw accel
    supportedHWAccel.push_back(HWAccelerators::NVIDIA);
  } else if (argumentParser.GPU_Provider == GPUProviders::INTEL) {
    // set encoders
    supportedEncoders.push_back(Encoders::AV1_QSV);
    supportedEncoders.push_back(Encoders::H264_QSV);
    supportedEncoders.push_back(Encoders::HEVC_QSV);
    // set decoders
    // supportedDecoders.push_back(Decoders::AV1_QSV);
    // supportedDecoders.push_back(Decoders::H264_QSV);
    // supportedDecoders.push_back(Decoders::HEVC_QSV);
    // set hw accel
    supportedHWAccel.push_back(HWAccelerators::INTEL);
  } else if (argumentParser.GPU_Provider == GPUProviders::AMD) {
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
    Log::debug(
        {"[UserSettings.cpp] Supported Encoder:", Encoders::getValue(encoder)});
  }

  // for (Decoders::Codec decoder : supportedDecoders) {
  //   Log::debug(
  //       {"[UserSettings.cpp] Supported Decoder:",
  //       Decoders::getValue(decoder)});
  // }
}

nlohmann::json ProgramSettings::asJSON() {
  nlohmann::json programSettings;

  programSettings["workingDir"] = ProgramSettings::workingDir;
  programSettings["runningEncoder"] = Encoders::getValue(this->runningEncoder);
  programSettings["runningHWAccel"] =
      HWAccelerators::getValue(this->runningHWAccel);

  return programSettings;
}
