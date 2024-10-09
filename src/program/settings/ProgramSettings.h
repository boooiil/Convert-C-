#ifndef PROGRAM_SETTINGS_H
#define PROGRAM_SETTINGS_H

// #include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
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
#include "enums/StringEnumDataHolder.h"

class ProgramSettings {
 public:
  ProgramSettings(void);
  ~ProgramSettings(void);

  /// @brief The current operating system of the user's machine
  StringEnumDataHolder<Platform> platform;
  /// @brief Current working directory.
  std::string workingDir;
  /// @brief List of supported encoders by the program.
  std::vector<StringEnumDataHolder<Encoders>> supportedEncoders;
  /// @brief List of supported hardware accelerators by the program.
  std::vector<StringEnumDataHolder<HWAccelerators>> supportedHWAccel;
  /// @brief List of regular expressions matching tunes.
  /// @brief The matching tunes can be used as an index
  /// @brief in the tuneAssociations list.
  std::vector<std::regex> tuneRegex;
  /// @brief List of tunes.
  std::vector<StringEnumDataHolder<Tunes>> tuneAssociations;

  // TODO: change this to a map vvvv
  /// @brief The current GPU of the user's machine
  std::vector<StringEnumDataHolder<GPUProviders>> GPU_Provider;

  /// @brief The current encoder being used
  StringEnumDataHolder<Encoders> runningEncoder;
  /// @brief The current decoder being used
  StringEnumDataHolder<HWAccelerators> runningHWAccel;

  void validateSettings(ArgumentParser& argumentParser);
  void gatherSystemDetails(void);

  nlohmann::json toJSON(void);
};

#endif  // PROGRAM_SETTINGS_H