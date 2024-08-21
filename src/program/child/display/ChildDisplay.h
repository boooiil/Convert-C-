#ifndef CHILD_DISPLAY_H
#define CHILD_DISPLAY_H

#include "../../generics/GenericDisplay.h"

class ChildDisplay : public GenericDisplay {
 public:
  void print(void);
  void printDebug(void);
  void printJSON(void);
};

#endif  // !CHILD_DISPLAY_H
