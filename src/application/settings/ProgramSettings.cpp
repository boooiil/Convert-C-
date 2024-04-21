#include "./ProgramSettings.h"

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// TODO: fill this out, rm ApplicationEncodingDecision

ProgramSettings::ProgramSettings() : runningEncoder(Encoders::Codec::HEVC) {
  char buff[FILENAME_MAX];

  if (GetCurrentDir(buff, FILENAME_MAX) != nullptr) {
    std::string tempStr = buff;
    ProgramSettings::workingDir = tempStr;
  } else {
    ProgramSettings::workingDir = "";
  }

  ProgramSettings::supportedEncoders = {Encoders::AV1,
                                        Encoders::AV1_AMF,
                                        Encoders::AV1_NVENC,
                                        Encoders::AV1_QSV,
                                        Encoders::H264,
                                        Encoders::H264_AMF,
                                        Encoders::H264_NVENC,
                                        Encoders::H264_QSV,
                                        Encoders::HEVC,
                                        Encoders::HEVC_AMF,
                                        Encoders::HEVC_NVENC,
                                        Encoders::HEVC_QSV

  };

  ProgramSettings::supportedHWAccel = {
      HWAccelerators::AMD, HWAccelerators::NVIDIA, HWAccelerators::INTEL};

  ProgramSettings::tuneRegex = {std::regex(R"(film)", std::regex::icase),
                                std::regex(R"(anim)", std::regex::icase),
                                std::regex(R"(grain)", std::regex::icase)};

  ProgramSettings::tuneAssociations = {Tunes::FILM, Tunes::ANIMATION,
                                       Tunes::GRAIN};
};

ProgramSettings::~ProgramSettings(void){};

void ProgramSettings::applySettings(UserSettings userSettings) {
  // guard against invalid encoder (should be handled in user settings)
  if (userSettings.wantedEncoder == Encoders::INVALID) {
    this->runningEncoder = Encoders::Codec::HEVC;
  } else {
    this->runningEncoder = userSettings.wantedEncoder;
  }

  if (!userSettings.supportedHWAccel.empty()) {
    this->runningHWAccel = userSettings.supportedHWAccel[0];
  }

  if (Encoders::isAV1(userSettings.wantedEncoder)) {
    userSettings.tune = Tunes::DEFAULT;
  }
};
