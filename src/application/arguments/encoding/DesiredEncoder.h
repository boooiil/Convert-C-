#ifndef DESIRED_ENCODER_H
#define DESIRED_ENCODER_H

#include "../../../ffmpeg/Encoders.h"
#include "../BaseArgument.h"

class DesiredEncoder : public BaseArgument<Encoders::Codec> {
 public:
  DesiredEncoder(void);
  ~DesiredEncoder(void);

  void parse(std::string) override;

  operator Encoders::Codec() const { return value; }
};

#endif  // DESIRED_ENCODER_H