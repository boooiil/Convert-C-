#ifndef PROGRAM_SETTINGS_H
#define PROGRAM_SETTINGS_H

#include <regex>

#include "../../ffmpeg/Decoders.h"
#include "../../ffmpeg/Encoders.h"
#include "../../ffmpeg/HWAccelerators.h"

class ProgramSettings {
 public:
  ProgramSettings(void);
  ~ProgramSettings(void);

  /// @brief Current working directory.
  std::string workingDir;
  /// @brief List of supported encoders by the program.
  std::vector<Encoders::Codec> supportedEncoders;
  /// @brief List of supported hardware accelerators by the program.
  std::vector<HWAccelerators::Accelerator> supportedHWAccel;
  /// @brief List of regular expressions matching tunes.
  /// @brief The matching tunes can be used as an index
  /// @brief in the tuneAssociations list.
  std::vector<std::regex> tuneRegex;
  /// @brief List of tunes.
  std::vector<std::string> tuneAssociations;

  /// @brief The current encoder being used
  Encoders::Codec runningEncoder;
  /// @brief The current decoder being used
  Decoders::Codec runningDecoder;
};

#endif  // PROGRAM_SETTINGS_H