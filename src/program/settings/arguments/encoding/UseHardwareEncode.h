#ifndef USE_HARDWARE_ENCODE_H
#define USE_HARDWARE_ENCODE_H

#include "../FlagArgument.h"

class UseHardwareEncode : public FlagArgument {
 public:
  UseHardwareEncode(void);
  ~UseHardwareEncode(void);

  void parse(std::string) override;

  UseHardwareEncode& operator=(const bool& provided);
};

#endif  // USE_HARDWARE_ENCODE_H