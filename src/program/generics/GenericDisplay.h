#ifndef GENERIC_DISPLAY_H
#define GENERIC_DISPLAY_H

class GenericDisplay {
 public:
  virtual ~GenericDisplay(void) = default;
  virtual void print(void) = 0;
  virtual void printDebug(void) = 0;
  virtual void printInformation(void) = 0;
  virtual void printJSON(void) = 0;
};
#endif  // !GENERIC_DISPLAY_H
