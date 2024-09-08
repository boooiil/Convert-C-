#ifndef PARENT_DISPLAY_H
#define PARENT_DISPLAY_H

#include "../../generics/GenericDisplay.h"

class ParentDisplay : public GenericDisplay {
 public:
  void print(void);
  void printDebug(void);
  void printInformation(void);
  void printJSON(void);
};

#endif  // !PARENT_DISPLAY_H
