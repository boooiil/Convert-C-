#include "NTicker.h"

#include <chrono>
#include <thread>

#include "../../logging/Log.h"
#include "../Program.h"
#include "../child/Child.h"
#include "../child/display/ChildDisplay.h"
#include "../parent/Parent.h"
#include "../parent/display/ParentDisplay.h"
#include "../settings/Help.h"
#include "nlohmann/json.hpp"

NTicker::NTicker(void) : endable(true) {
  this->display = nullptr;
  this->runner = nullptr;
}

void NTicker::determineNextAction(void) {
  if (Program::settings->argumentParser->printHelp) {
    Help::printHelp();
    Program::stopFlag = true;
  } else if (Program::settings->argumentParser->printInformation) {
    // print information
    this->runner->prepare();
    this->display->printInformation();
    Program::stopFlag = true;
  } else {
    // prepare runner
    this->runner->prepare();
  }
  // if (print help) display help
  // if (print information) print information
  //   print media information for child
  //   print directory informattion for parent
  // else start ticker
  // end ticker
}

void NTicker::prepare(void) {
  // use parent display
  if (Program::settings->argumentParser->isParent) {
    Log::debug({"[NTicker.cpp] Running as parent."});
    this->display = new ParentDisplay();
    this->runner = new Parent();
  } else {
    Log::debug({"[NTicker.cpp] Running as child."});
    this->display = new ChildDisplay();
    this->runner = new Child();
  }

  this->determineNextAction();
}

void NTicker::run(void) {
  while (!Program::stopFlag) {
    this->runner->run();
    this->display->print();

    std::this_thread::sleep_for(std::chrono::milliseconds(
        Program::settings->argumentParser->displayRefresh));
  }
  // if (Program::settings->argumentParser->isParent) {
  //   // parent display
  //   this->display->print();
  // } else {
  //   // child display
  //   this->display->print();
  // }
}

void NTicker::end(void) {
  Log::debug({"[NTicker.cpp] Ending ticker."});
  Log::debug({"[NTicker.cpp] Expected to delete { display, runner }."});

  if (this->display != nullptr) {
    Log::debug({"[NTicker.cpp] Deleting display."});
    delete this->display;
  }

  if (this->runner != nullptr) {
    while (!this->runner->isEndable()) {
      Log::debug({"[NTicker.cpp] Waiting for runner to end."});

      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      // while (!Program::ticker->runner->isEndable()
      // wait for runner to end
    }
    this->runner->end();

    Log::debug({"[NTicker.cpp] Deleting runner."});
    delete this->runner;
  }
}

void NTicker::setEndable(bool flag) {
  Log::debug(
      {"Parent has been set as endable:", this->endable ? "True" : "False"});
  this->endable = flag;
}

bool NTicker::isEndable(void) { return this->endable; }

void NTicker::fromJSON(nlohmann::json) {
  // read json information
}

nlohmann::json NTicker::asJSON(void) {
  using namespace nlohmann;

  json program;

  if (this->runner == nullptr) {
    program["Runner"] = {};
  } else {
    program["Runner"] = this->runner->asJSON();
  }

  return program;
}

void NTicker::writeDebug(void) {
  // write debug information
}
