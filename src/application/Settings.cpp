#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include "Settings.h"

Settings::Settings() {
  char buff[FILENAME_MAX];

  if (GetCurrentDir(buff, FILENAME_MAX) != nullptr) {
    std::string tempStr = buff;
    Settings::workingDir = tempStr;
  } else {
    Settings::workingDir = "";
  }

  Settings::supportedEncoders = {Encoders::AV1,
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

  Settings::supportedHWAccel = {HWAccelerators::AMD, HWAccelerators::NVIDIA,
                                HWAccelerators::INTEL};

  Settings::tuneRegex = {std::regex(R"(film)", std::regex::icase),
                         std::regex(R"(anim)", std::regex::icase),
                         std::regex(R"(grain)", std::regex::icase)};

  Settings::tuneAssociations = {"film", "animation", "grain"};
}

Settings::~Settings() {}