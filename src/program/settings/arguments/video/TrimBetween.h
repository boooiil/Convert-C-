#ifndef TRIM_BETWEEN_H
#define TRIM_BETWEEN_H

#include "../VectorArgument.h"

class TrimBetween : public VectorArgument<std::string> {
 public:
  TrimBetween(void);
  ~TrimBetween(void);

  void parse(std::string argument) override;
};

#endif  // TRIM_BETWEEN_H