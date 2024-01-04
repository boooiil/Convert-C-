/*********************************************************************
 * @file   Settings.h
 * @brief  Settings class header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef SETTINGS
#define SETTINGS

#include <regex>

#include "../ffmpeg/Encoders.h"
#include "../ffmpeg/HWAccelerators.h"

/**
 * @brief Holds all settings for the application.
 */
class Settings {
 public:
  Settings(void);
  ~Settings(void);

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
};

#endif  //! SETTINGS
