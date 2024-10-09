#include "Program.h"

#include <chrono>
#include <fstream>
#include <iosfwd>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

#include "../utils/logging/LogColor.h"
#include "../utils/logging/Logger.h"
#include "generics/GenericRunner.h"
#include "generics/JSONSerializableRunner.h"
#include "settings/Settings.h"
#include "settings/enums/LoggingOptions.h"
#include "ticker/NTicker.h"

JSONSerializableRunner* Program::ticker = nullptr;
// Log* Program::log = nullptr;
Settings* Program::settings = nullptr;
bool Program::stopFlag = false;

Program::Program(void) : endable(true) {}
Program::~Program(void) {
  // should always call end
  // this->end();
}

void Program::prepare() {}

void Program::prepare(int argc, char* argv[]) {
  // Program::log = new Log();
  Program::ticker = new NTicker();

  Program::settings = new Settings();
  Program::settings->init(argc, argv);

  if (!stopFlag) Program::ticker->prepare();
}

void Program::run() {
  if (!stopFlag) Program::ticker->run();
}

void Program::end(void) {
  LOG_DEBUG("Ending program.");
  LOG_DEBUG("Expected to delete { log, ticker, settings }.");

  Program::stopFlag = true;

  if (LoggingOptions::isDebug(
          Program::settings->argumentParser->loggingFormat.get())) {
    LOG_DEBUG("Saving debug file.");

    std::ofstream oFile("container_debug.json");

    if (!oFile.is_open()) {
      LOG(LogColor::fgRed("Failed to open debug file->"));
      return;
    }

    oFile << Program::toJSON().dump(4);
    oFile.close();
  }

  if (Program::ticker != nullptr) {
    LOG_DEBUG("Deleting ticker.");
    Program::ticker->end();
    delete Program::ticker;
  }

  /*if (Program::log != nullptr) {
    Program::log->end();
    LOG_DEBUG("Deleting log.");
    delete Program::log;
  }*/

  if (Program::settings != nullptr) {
    LOG_DEBUG("Deleting settings.");
    delete Program::settings;
  }

  // TODO: end needs to exit program
  // add ticker
}

void Program::setEndable(bool flag) {
  LOG_DEBUG("Program has been set as endable:",
            Program::stopFlag ? "True" : "False");
  Program::stopFlag = flag;
}

bool Program::isEndable() { return Program::stopFlag; }

void Program::fromJSON(nlohmann::json program) {}

nlohmann::json Program::toJSON() {
  using namespace nlohmann;

  json program;
  json settings_json = Program::settings->toJSON();

  program["Settings"] = settings_json;

  if (Program::ticker != nullptr) {
    program["Ticker"] = Program::ticker->toJSON();
  }

  return program;
}
