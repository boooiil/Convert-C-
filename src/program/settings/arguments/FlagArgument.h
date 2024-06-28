#ifndef FLAG_ARGUMENT_H
#define FLAG_ARGUMENT_H

#include "./BaseArgument.h"

class FlagArgument : public BaseArgument<bool> {
 public:
  operator std::string(void) const { return value ? "true" : "false"; };
  operator const char*(void) const { return value ? "true" : "false"; };

  bool operator!(void) const { return !value; };

  std::string toString() const { return value ? "true" : "false"; };

  virtual FlagArgument& operator=(const bool& provided) = 0;
};

#endif  // FLAG_ARGUMENT_H