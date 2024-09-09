#ifndef PROGRAM_SETTINGS_H
#define PROGRAM_SETTINGS_H

#include <nlohmann/json.hpp>
#include <regex>
#include <string>
#include <vector>

#include "../settings/arguments/ArgumentParser.h"
#include "../settings/enums/Decoders.h"
#include "../settings/enums/Encoders.h"
#include "../settings/enums/HWAccelerators.h"
#include "../settings/enums/Tunes.h"
#include "enums/GPUProviders.h"
#include "enums/Platform.h"

class ProgramSettings {
 public:
  ProgramSettings(void);
  ~ProgramSettings(void);

  /// @brief The current operating system of the user's machine
  Platform::OPERATING_SYSTEM platform;
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
  std::vector<Tunes::Tune> tuneAssociations;

  // TODO: change this to a map vvvv
  /// @brief The current GPU of the user's machine
  std::vector<GPUProviders::Provider> GPU_Provider;

  /// @brief The current encoder being used
  Encoders::Codec runningEncoder;
  /// @brief The current decoder being used
  HWAccelerators::Accelerator runningHWAccel;

  void validateSettings(ArgumentParser& argumentParser);
  void gatherSystemDetails(void);

  nlohmann::json asJSON(void);
};

#endif  // PROGRAM_SETTINGS_H