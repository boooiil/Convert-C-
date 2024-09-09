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
#include "../../utils/ListUtils.h"
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
    : GPU_Provider(GPUProviders::Provider::UNKNOWN),
      platform(Platform::OPERATING_SYSTEM::UNKNOWN),
      runningEncoder(Encoders::Codec::HEVC),
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

void ProgramSettings::validateSettings(ArgumentParser& argumentParser) {
  // guard against invalid encoder (should be handled in user settings)
  if (argumentParser.wantedEncoder == Encoders::INVALID) {
    this->runningEncoder = Encoders::Codec::HEVC;
  } else {
    this->runningEncoder = argumentParser.wantedEncoder;
  }

  if (!this->supportedHWAccel.empty()) {
    this->runningHWAccel = this->supportedHWAccel[0];
  }

  if (Encoders::isAV1(argumentParser.wantedEncoder)) {
    argumentParser.tune = Tunes::DEFAULT;
  }

  Log::debug({"[ProgramSettings.cpp] Running Encoder:",
              Encoders::getValue(this->runningEncoder)});

  // hevc does not support film tune
  // i'm sure av1 does not as well
  if (argumentParser.tune == Tunes::FILM &&
      Encoders::isHEVC(argumentParser.wantedEncoder)) {
    Log::debug({"[ProgramSettings.cpp] HEVC does not support film tune."});
    argumentParser.tune = Tunes::DEFAULT;
  }

  Log::debug({"[ProgramSettings.cpp] Running Tune:",
              Tunes::getValue(argumentParser.tune)});
};

void ProgramSettings::gatherSystemDetails(void) {
#ifdef _WIN32
  this->platform = Platform::WINDOWS;

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

  Log::debug({"[ProgramSettings.cpp (win)] GPU Provider Raw:", result});

  // nvidia
  if (RegexUtils::isMatch(result, "nvidia", std::regex_constants::icase)) {
    this->GPU_Provider.push_back(GPUProviders::NVIDIA);
  }
  // intel
  if (RegexUtils::isMatch(result, "intel", std::regex_constants::icase)) {
    this->GPU_Provider.push_back(GPUProviders::INTEL);
  }
  // amd
  if (RegexUtils::isMatch(result, "amd", std::regex_constants::icase)) {
    this->GPU_Provider.push_back(GPUProviders::AMD);
  }
  // unknown
  if (this->GPU_Provider.empty()) {
    this->GPU_Provider.push_back(GPUProviders::UNKNOWN);
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

  Log::debug({"[ProgramSettings.cpp (unix)] GPU Provider Raw:", result});

  // nvidia
  if (RegexUtils::isMatch(result, "nvidia", std::regex_constants::icase)) {
    this->GPU_Provider.push_back(GPUProviders::NVIDIA);
  }
  // intel
  if (RegexUtils::isMatch(result, "intel", std::regex_constants::icase)) {
    this->GPU_Provider.push_back(GPUProviders::INTEL);
  }
  // amd
  if (RegexUtils::isMatch(result, "amd", std::regex_constants::icase)) {
    this->GPU_Provider.push_back(GPUProviders::AMD);
  }
  // unknown
  if (this->GPU_Provider.empty()) {
    this->GPU_Provider.push_back(GPUProviders::UNKNOWN);
  }

#else
  throw std::runtime_error("Unsupported platform!");
#endif

  GPUProviders::Provider preferredProvider =
      GPUProviders::getPreferred(this->GPU_Provider);

  Log::debug(
      {"[ProgramSettings.cpp] Platform:", Platform::getValue(this->platform)});

  Log::debug({"[ProgramSettings.cpp] Preferred GPU Provider:",
              GPUProviders::getValue(preferredProvider)});

  if (ListUtils::contains(this->GPU_Provider, GPUProviders::NVIDIA)) {
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
  }
  if (ListUtils::contains(this->GPU_Provider, GPUProviders::INTEL)) {
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
  }
  if (ListUtils::contains(this->GPU_Provider, GPUProviders::AMD)) {
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
    Log::debug({"[ProgramSettings.cpp] Supported Encoder:",
                Encoders::getValue(encoder)});
  }

  for (HWAccelerators::Accelerator hwAccel : supportedHWAccel) {
    Log::debug({"[ProgramSettings.cpp] Supported HW Accel:",
                HWAccelerators::getValue(hwAccel)});
  }

  // for (Decoders::Codec decoder : supportedDecoders) {
  //   Log::debug(
  //       {"[ProgramSettings.cpp] Supported Decoder:",
  //       Decoders::getValue(decoder)});
  // }
}

nlohmann::json ProgramSettings::asJSON() {
  nlohmann::json programSettings;

  programSettings["supported_encoders"] = nlohmann::json::array();
  programSettings["supported_decoders"] = nlohmann::json::array();
  programSettings["supported_hw_accel"] = nlohmann::json::array();

  programSettings["workingDir"] = ProgramSettings::workingDir;
  programSettings["runningEncoder"] = Encoders::getValue(this->runningEncoder);
  programSettings["runningHWAccel"] =
      HWAccelerators::getValue(this->runningHWAccel);

  programSettings["platform"] = Platform::getValue(this->platform);
  programSettings["gpu_provider"] =
      GPUProviders::getValue(GPUProviders::getPreferred(this->GPU_Provider));

  for (auto encoder : this->supportedEncoders) {
    programSettings["supported_encoders"].push_back(
        Encoders::getValue(encoder));
  }

  /*for (auto decoder : this->supportedDecoders) {
    programSettings["supported_decoders"].push_back(Decoders::getValue(decoder));
  }*/

  for (auto hw_accel : this->supportedHWAccel) {
    programSettings["supported_hw_accel"].push_back(
        HWAccelerators::getValue(hw_accel));
  }

  return programSettings;
}
