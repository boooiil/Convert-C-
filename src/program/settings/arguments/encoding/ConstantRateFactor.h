#ifndef CONSTANT_RATE_FACTOR_H
#define CONSTANT_RATE_FACTOR_H

#include "../IntegerArgument.h"

class ConstantRateFactor : public IntegerArgument {
 public:
  ConstantRateFactor(void);
  ~ConstantRateFactor(void);

  void parse(std::string) override;
};

#endif  // CONSTANT_RATE_FACTOR_H