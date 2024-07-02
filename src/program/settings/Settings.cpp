#include "Settings.h"

#include "../../logging/Log.h"

Settings::Settings(int argc, char* argv[]) {

  Log::debug({"[Settings.cpp] Creating settings object with (",
              std::to_string(argc), ") args."});

  Log::debug({"[Settings.cpp] Creating argument parser object."});
  this->argumentParser = new ArgumentParser();
  this->argumentParser->parse(argc, argv);

  Log::debug({"[Settings.cpp] Creating program settings object."});
  this->programSettings = new ProgramSettings();
  this->programSettings->applySettings(*this->argumentParser);
}

Settings::~Settings() {
  if (this->argumentParser != nullptr) {
    Log::debug({"[Settings.cpp] Deleting argument parser"});
    delete this->argumentParser;
  }
  if (this->programSettings != nullptr) {
    Log::debug({"[Settings.cpp] Deleting program settings"});
    delete this->programSettings;
  }
}
