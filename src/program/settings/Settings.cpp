#include "Settings.h"

#include <nlohmann/json.hpp>
#include <string>

#include "../../logging/Log.h"
#include "ProgramSettings.h"
#include "arguments/ArgumentParser.h"

Settings::Settings() : argumentParser(nullptr), programSettings(nullptr) {}

Settings::~Settings() {
  Log::debug(
      {"[Settings.cpp] Expected to delete { programSettings, argumentParser "
       "}."});
  if (this->programSettings != nullptr) {
    Log::debug({"[Settings.cpp] Deleting program settings"});
    delete this->programSettings;
  }
  if (this->argumentParser != nullptr) {
    Log::debug({"[Settings.cpp] Deleting argument parser"});
    delete this->argumentParser;
  }
}

void Settings::init(int argc, char* argv[]) {
  // Log::debug({"[Settings.cpp] Creating settings object with (",
  //             std::to_string(argc), ") args."});

  // Log::debug({"[Settings.cpp] Creating argument parser object."});
  this->argumentParser = new ArgumentParser();
  this->argumentParser->parse(argc, argv);

  Log::debug({"[Settings.cpp] Creating program settings object."});
  this->programSettings = new ProgramSettings();
  this->programSettings->gatherSystemDetails();
  this->programSettings->validateSettings(*this->argumentParser);
  Log::debug({"[Settings.cpp] Settings initialized.",
              "tune: ", Tunes::getValue(this->argumentParser->tune)});
}

nlohmann::json Settings::asJSON() {
  using namespace nlohmann;

  json settings;

  settings["ArgumentParser"] = this->argumentParser->asJSON();
  settings["ProgramSettings"] = this->programSettings->asJSON();

  return settings;
}
