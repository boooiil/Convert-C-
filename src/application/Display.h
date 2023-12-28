#ifndef DISPLAY_H
#define DISPLAY_H

#include "./Container.h"

class Display {
 public:
  Display(Container& container);
  ~Display();

  void print();
  void printDebug();

 private:
  Container& container;
};

#endif  // !DISPLAY_H
