#ifndef SETTINGS_H
#define SETTINGS_H

#include "arguments/ArgumentParser.h"
#include "ProgramSettings.h"

class Settings {
 public:
  Settings(int argc, char* argv[]);
  ~Settings();

  ArgumentParser* argumentParser;
  ProgramSettings* programSettings;

};

#endif  // !SETTINGS_H
