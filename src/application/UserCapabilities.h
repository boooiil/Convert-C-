/*********************************************************************
 * @file   UserCapabilities.h
 * @brief  UserCapabilities class header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef USER_CAPABILITIES
#define USER_CAPABILITIES

#include <vector>

#include "../ffmpeg/Decoders.h"
#include "../ffmpeg/Encoders.h"
#include "Platform.h"

/**
 * @brief This class is used to find the hardware details of the user's machine
 */
class UserCapabilities {
 public:
  UserCapabilities(void);
  ~UserCapabilities(void);

  /// @brief The current operating system of the user's machine
  Platform::OPERATING_SYSTEM platform;
  /// @brief The current GPU of the user's machine
  const char* GPU_Provider;
  /// @brief The supported encoders
  std::vector<Encoders::Codec> supportedEncoders;
  /// @brief The supported decoders
  std::vector<Decoders::Codec> supportedDecoders;

  /**
   * @brief Finds the hardware details of the user's machine
   * @return void
   */
  void findHardwareDetails(void);
};

#endif  // !USER_CAPABILITIES
