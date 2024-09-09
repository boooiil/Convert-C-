#include "Program.h"

#include <chrono>
#include <fstream>
#include <iosfwd>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

#include "../logging/Log.h"
#include "../logging/LogColor.h"
#include "generics/GenericRunner.h"
#include "generics/JSONSerializableRunner.h"
#include "settings/Settings.h"
#include "settings/enums/LoggingOptions.h"
#include "ticker/NTicker.h"

JSONSerializableRunner* Program::ticker = nullptr;
// Log* Program::log = nullptr;
Settings* Program::settings = nullptr;
bool Program::stopFlag = false;

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
  Log::debug({"[Program.cpp] Ending program."});
  Log::debug({"[Program.cpp] Expected to delete { log, ticker, settings }."});

  Program::stopFlag = true;

  if (LoggingOptions::isDebug(
          Program::settings->argumentParser->loggingFormat.get())) {
    Log::debug({"[Program.cpp] Saving debug file."});

    std::ofstream oFile("container_debug.json");

    if (!oFile.is_open()) {
      Log::send({LogColor::fgRed("Failed to open debug file->")});
      return;
    }

    oFile << Program::asJSON().dump(4);
    oFile.close();
  }

  if (Program::ticker != nullptr) {
    Log::debug({"[Program.cpp] Deleting ticker."});
    Program::ticker->end();
    delete Program::ticker;
  }

  /*if (Program::log != nullptr) {
    Program::log->end();
    Log::debug({"[Program.cpp] Deleting log."});
    delete Program::log;
  }*/

  if (Program::settings != nullptr) {
    Log::debug({"[Program.cpp] Deleting settings."});
    delete Program::settings;
  }

  // TODO: end needs to exit program
  // add ticker
}

void Program::setEndable(bool flag) {
  Log::debug({"Program has been set as endable:",
              Program::stopFlag ? "True" : "False"});
  Program::stopFlag = flag;
}

bool Program::isEndable() { return Program::stopFlag; }

nlohmann::json Program::asJSON() {
  using namespace nlohmann;

  json program;
  json settings_json = Program::settings->asJSON();

  program["Settings"] = settings_json;

  if (Program::ticker != nullptr) {
    program["Ticker"] = Program::ticker->asJSON();
  }

  return program;
}
