#ifndef DEBUG_H
#define DEBUG_H

#include "../FlagArgument.h"

class Debug : public FlagArgument {
 public:
  Debug(void);
  ~Debug(void);

  void parse(std::string) override;

  Debug& operator=(const bool& provided) override;
};

#endif  // DEBUG_H