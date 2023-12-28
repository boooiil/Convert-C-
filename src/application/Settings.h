
#ifndef SETTINGS
#define SETTINGS

#include <regex>

#include "../ffmpeg/Encoders.h"
#include "../ffmpeg/HWAccelerators.h"

class Settings {
 public:
  Settings();
  ~Settings();

  std::string workingDir;
  std::vector<Encoders::Codec> supportedEncoders;
  std::vector<HWAccelerators::Accelerator> supportedHWAccel;

  std::vector<std::regex> tuneRegex;
  std::vector<std::string> tuneAssociations;
};

#endif  //! SETTINGS
