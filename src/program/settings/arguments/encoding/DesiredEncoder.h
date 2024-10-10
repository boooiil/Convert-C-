#ifndef DESIRED_ENCODER_H
#define DESIRED_ENCODER_H

#include <string>

#include "../../enums/Encoders.h"
#include "../../enums/StringEnumDataHolder.h"
#include "../BaseArgument.h"

class DesiredEncoder : public BaseArgument<StringEnumDataHolder<Encoders>> {
 public:
  DesiredEncoder(void);

  ~DesiredEncoder(void);

  void parse(std::string) override;

  // Inherited via BaseArgument
  const std::string toString(void) const override;
  const bool hasData(void) const override;
};

#endif  // DESIRED_ENCODER_H