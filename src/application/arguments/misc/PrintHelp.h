#ifndef PRINT_HELP_H
#define PRINT_HELP_H

#include "../FlagArgument.h"

class PrintHelp : public FlagArgument {
 public:
  PrintHelp(void);
  ~PrintHelp(void);

  void parse(std::string) override;

  PrintHelp& operator=(const bool& provided) override;
};

#endif  // PRINT_HELP_H