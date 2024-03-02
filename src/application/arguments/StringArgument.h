#ifndef STRING_ARGUMENT_H
#define STRING_ARGUMENT_H

#include "./BaseArgument.h"

class StringArgument : public BaseArgument<std::string> {
 public:
  operator const char*(void) const { return value.c_str(); };
  std::string operator+(const char* str) { return value + str; };
  std::string operator+(const std::string& str) { return value + str; };

  std::string asString(void) { return value; };
  const char* c_str(void) { return value.c_str(); };
};

#endif  // STRING_ARGUMENT_H