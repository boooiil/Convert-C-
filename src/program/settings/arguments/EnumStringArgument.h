#ifndef ENUM_STRING_ARGUMENT_H
#define ENUM_STRING_ARGUMENT_H

#include <type_traits>

#include "../enums/StringEnumDataHolder.h"
#include "BaseArgument.h"

/**
 * EnumArgument : public BaseArgument<StringEnumDataHolder<T>>
 */
template <typename T>
class EnumStringArgument : public BaseArgument<StringEnumDataHolder<T>> {
 public:
  EnumStringArgument(std::string _helpMessage, std::string _flag,
                     std::string _longFlag, int data)
      : BaseArgument<StringEnumDataHolder<T>>(_helpMessage, _flag, _longFlag,
                                              data) {}

  ~EnumStringArgument() {}

  void parse(std::string argument) override {
    // TODO: figure out how to do this
  }

  const std::string toString(void) const {
    // TODO: figure out how to do this
    return "";
  }

  const bool hasData(void) const { return true; }
};

#endif  // ENUM_STRING_ARGUMENT_H