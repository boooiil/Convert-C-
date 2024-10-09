#ifndef ENUM_ARGUMENT_H
#define ENUM_ARGUMENT_H

#include <type_traits>

#include "BaseArgument.h"

template <typename T,
          typename std::enable_if<std::is_base_of<T, T>::value>::type* =
              nullptr>
class EnumArgument : BaseArgument<T> {
 public:
};

#endif  // ENUM_ARGUMENT_H