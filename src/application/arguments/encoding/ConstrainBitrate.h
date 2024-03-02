#ifndef CONSTRAIN_BITRATE_H
#define CONSTRAIN_BITRATE_H

#include "../FlagArgument.h"

class ConstrainBitrate : public FlagArgument {
 public:
  ConstrainBitrate(void);
  ~ConstrainBitrate(void);

  void parse(std::string) override;

  ConstrainBitrate& operator=(const bool& provided);
};

#endif  // CONSTRAIN_BITRATE_H