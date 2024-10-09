#include "Settings.h"

#include <nlohmann/json.hpp>
#include <string>

#include "../../utils/logging/Logger.h"
#include "ProgramSettings.h"
#include "arguments/ArgumentParser.h"
#include "enums/Tunes.h"

Settings::Settings() : argumentParser(nullptr), programSettings(nullptr) {}

Settings::~Settings() {
  LOG_DEBUG("deleting { programSettings, argumentParser }");
  if (this->programSettings != nullptr) {
    LOG_DEBUG("Deleting program settings");
    delete this->programSettings;
  }
  if (this->argumentParser != nullptr) {
    LOG_DEBUG("Deleting argument parser");
    delete this->argumentParser;
  }
}

void Settings::init(int argc, char* argv[]) {
  // LOG_DEBUG("Creating settings object with (",
  //             std::to_string(argc), ") args.");

  // LOG_DEBUG("Creating argument parser object.");
  this->argumentParser = new ArgumentParser();
  this->argumentParser->prepare();
  this->argumentParser->parse(argc, argv);

  LOG_DEBUG("Creating program settings object.");
  this->programSettings = new ProgramSettings();
  this->programSettings->gatherSystemDetails();
  this->programSettings->validateSettings(*this->argumentParser);
  LOG_DEBUG("Settings initialized.",
            "tune: ", this->argumentParser->tune.getName());
}

nlohmann::json Settings::toJSON() {
  using namespace nlohmann;

  json settings;

  settings["ArgumentParser"] = this->argumentParser->toJSON();
  settings["ProgramSettings"] = this->programSettings->toJSON();

  return settings;
}
