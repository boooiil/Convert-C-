#ifndef DESIRED_ENCODER_H
#define DESIRED_ENCODER_H

#include <string>

#include "../../enums/Encoders.h"
#include "../BaseArgument.h"

class DesiredEncoder : public BaseArgument<Encoders::Codec> {
 public:
  DesiredEncoder(void);

  ~DesiredEncoder(void);

  void parse(std::string) override;

  operator Encoders::Codec() const { return value; }

  // Inherited via BaseArgument
  const std::string toString(void) const override;
  const bool hasData(void) const override;
};

#endif  // DESIRED_ENCODER_H