#ifndef SETTINGS_H
#define SETTINGS_H

#include "arguments/ArgumentParser.h"

class Settings {
 public:
  Settings(int argc, char* argv[]);
  ~Settings();

  ArgumentParser* argumentParser;
};

#endif  // !SETTINGS_H
