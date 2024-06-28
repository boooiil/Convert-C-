#ifndef INTEGER_ARGUMENT_H
#define INTEGER_ARGUMENT_H

#include "./BaseArgument.h"

class IntegerArgument : public BaseArgument<int> {
 public:
  operator std::string(void) const { return std::to_string(value); };

  std::string asString(void) { return std::to_string(value); };
};

#endif  // INTEGER_ARGUMENT_H