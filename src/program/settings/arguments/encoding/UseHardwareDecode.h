#ifndef USE_HARDWARE_DECODE_H
#define USE_HARDWARE_DECODE_H

#include "../FlagArgument.h"

class UseHardwareDecode : public FlagArgument {
 public:
  UseHardwareDecode(void);
  ~UseHardwareDecode(void);

  void parse(std::string) override;

  UseHardwareDecode& operator=(const bool& provided);
};

#endif  // USE_HARDWARE_DECODE_H