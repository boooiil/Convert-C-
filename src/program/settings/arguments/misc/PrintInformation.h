#ifndef PRINT_INFORMATION_H
#define PRINT_INFORMATION_H

#include "../FlagArgument.h"

class PrintInformation : public FlagArgument {
 public:
  PrintInformation(void);
  ~PrintInformation(void);

  void parse(std::string) override;

  PrintInformation& operator=(const bool& provided) override;
};

#endif  // PRINT_INFORMATION_H