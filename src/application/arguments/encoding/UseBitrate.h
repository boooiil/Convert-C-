#ifndef USE_BITRATE_H
#define USE_BITRATE_H

#include "../FlagArgument.h"

class UseBitrate : public FlagArgument {
 public:
  UseBitrate(void);
  ~UseBitrate(void);

  void parse(std::string) override;

  UseBitrate& operator=(const bool& provided);
};

#endif  // USE_BITRATE_H