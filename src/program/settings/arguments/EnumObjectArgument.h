#ifndef ENUM_OBJECT_ARGUMENT_H
#define ENUM_OBJECT_ARGUMENT_H

#include <type_traits>

#include "../enums/ObjectEnumDataHolder.h"
#include "BaseArgument.h"

/**
 * EnumArgument : public BaseArgument<StringEnumDataHolder<T>>
 */
template <typename T>
class EnumObjectArgument : public BaseArgument<ObjectEnumDataHolder<T>> {
public:
  EnumObjectArgument(std::string _helpMessage, std::string _flag,
    std::string _longFlag, int data)
    : BaseArgument(_helpMessage, _flag, _longFlag, data) {}

  ~EnumObjectArgument() {}

  void parse(std::string argument) override {}

  const std::string toString(void) const {
    return std::to_string();
  }

  const bool hasData(void) const { return true; }
};

#endif  // ENUM_OBJECT_ARGUMENT_H