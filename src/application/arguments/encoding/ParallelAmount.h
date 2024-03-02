#ifndef PARALLEL_AMOUNT_H
#define PARALLEL_AMOUNT_H

#include "../IntegerArgument.h"

class ParallelAmount : public IntegerArgument {
 public:
  ParallelAmount(void);
  ~ParallelAmount(void);

  void parse(std::string) override;
};

#endif  // PARALLEL_AMOUNT_H