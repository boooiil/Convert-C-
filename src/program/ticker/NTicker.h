#pragma once

#include "../generics/GenericDisplay.h"
#include "../generics/GenericRunner.h"

class NTicker : GenericRunner {
 public:
  void determineNextAction(void);
  void prepare(void);
  void start(void);
  void end(void);

  const char* getType(void) const;
  void setType(const char*);

 private:
  GenericDisplay* display;
  void writeDebug(void);
};
