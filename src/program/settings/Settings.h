#ifndef SETTINGS_H
#define SETTINGS_H

#include <nlohmann/json_fwd.hpp>

#include "ProgramSettings.h"
#include "arguments/ArgumentParser.h"

class Settings {
 public:
  Settings(void);
  ~Settings(void);

  ArgumentParser* argumentParser;
  ProgramSettings* programSettings;

  void init(int argc, char* argv[]);

  nlohmann::json toJSON(void);
};

#endif  // !SETTINGS_H
