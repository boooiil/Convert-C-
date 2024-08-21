#include "Program.h"

#include <nlohmann/json.hpp>

#include "../logging/Log.h"
#include "child/Child.h"
#include "generics/JSONSerializableRunner.h"
#include "parent/Parent.h"
#include "settings/Settings.h"

JSONSerializableRunner* Program::runner = nullptr;
Log* Program::log = nullptr;
Settings* Program::settings = nullptr;

void Program::prepare(void) {}

void Program::run(int argc, char* argv[]) {
  Program::log = new Log();

  Program::settings = new Settings();
  Program::settings->init(argc, argv);

  if (Program::settings->argumentParser->isParent) {
    Log::debug({"[Program.cpp] Running as parent."});
    Program::runner = new Parent();
  } else {
    Log::debug({"[Program.cpp] Running as child."});
    Program::runner = new Child();
  }

  Program::runner->prepare();
  Program::runner->run();
}

void Program::end(void) {
  if (Program::runner != nullptr) {
    Log::debug({"[Program.cpp] Ending runner."});
    Program::runner->end();
  }

  if (Program::runner != nullptr) {
    Log::debug({"[Program.cpp] Deleting runner."});
    delete Program::runner;
  }

  if (Program::log != nullptr) {
    Log::debug({"[Program.cpp] Deleting log."});
    delete Program::log;
  }

  if (Program::settings != nullptr) {
    Log::debug({"[Program.cpp] Deleting settings."});
    delete Program::settings;
  }

  // TODO: end needs to exit program
  // add ticker
}

nlohmann::json Program::asJSON() {
  using namespace nlohmann;

  json program;
  json settings_json = Program::settings->asJSON();

  program["Settings"] = settings_json;

  if (Program::runner != nullptr) {
    program["Runner"] = Program::runner->asJSON();
  }

  return program;
}
