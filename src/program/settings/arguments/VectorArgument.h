#ifndef VECTOR_ARGUMENT_H
#define VECTOR_ARGUMENT_H

#include <vector>

#include "./BaseArgument.h"

template <typename T>
class VectorArgument : public BaseArgument<std::vector<T>> {
 public:
};

#endif  // VECTOR_ARGUMENT_H