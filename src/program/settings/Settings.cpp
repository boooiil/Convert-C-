#include "Settings.h"

#include "../../logging/Log.h"

Settings::Settings(int argc, char* argv[]) {
  this->argumentParser = new ArgumentParser();
  this->argumentParser->parse(argc, argv);
}

Settings::~Settings() {
  if (this->argumentParser != nullptr) {
    Log::debug({"[Settings.cpp] Deleting argument parser"});
    delete this->argumentParser;
  }
}
