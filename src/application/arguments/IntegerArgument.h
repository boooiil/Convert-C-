#ifndef INTEGER_ARGUMENT_H
#define INTEGER_ARGUMENT_H

#include "./BaseArgument.h"

class IntegerArgument : public BaseArgument<int> {
 public:
  operator std::string(void) const { return std::to_string(value); };
  operator const char*(void) const { return std::to_string(value).c_str(); };

  std::string asString(void) { return std::to_string(value); };
  const char* c_str(void) { return asString().c_str(); };
};

#endif  // INTEGER_ARGUMENT_H