#ifndef PROGRAM_H
#define PROGRAM_H

#include "child/Child.h"
#include "parent/Parent.h"
#include "settings/Settings.h"

class Program {
 public:
  Program();
  ~Program();

  static Settings* settings;
  static Parent* parent;
  static Child* child;

  static void run(int argc, char* argv[]);
  static void end(void);
};

#endif  // !PROGRAM_H