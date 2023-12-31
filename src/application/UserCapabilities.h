#ifndef USER_CAPABILITIES
#define USER_CAPABILITIES

#include <vector>

#include "../ffmpeg/Decoders.h"
#include "../ffmpeg/Encoders.h"
#include "Platform.h"

class UserCapabilities {
 public:
  UserCapabilities(void);
  ~UserCapabilities(void);

  Platform::OPERATING_SYSTEM platform;
  const char* GPU_Provider;
  std::vector<Encoders::Codec> supportedEncoders;
  std::vector<Decoders::Codec> supportedDecoders;

  /**
   * @brief Finds the hardware details of the user's machine
   * @return void
   */
  void findHardwareDetails(void);
};

#endif  // !USER_CAPABILITIES
