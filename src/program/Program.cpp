#include "Program.h"
#include "../logging/Log.h"

Program::Program() {}

Program::~Program() {
  if (this->parent != nullptr) {
    Log::debug({"[Program.cpp] Deleting parent."});
    delete this->parent;
  }

  if (this->child != nullptr) {
    Log::debug({"[Program.cpp] Deleting child."});
    delete this->child;
  }

  if (this->settings != nullptr) {
    Log::debug({"[Program.cpp] Deleting settings."});
    delete this->settings;
  }
}

void Program::run(int argc, char* argv[]) {
  Program::settings = new Settings(argc, argv);

  if (Program::settings->argumentParser->isParent) {
    Log::debug({"[Program.cpp] Running as parent."});
    Program::parent = new Parent();
    Program::parent->prepare();
    Program::parent->run();
  } else {
    Log::debug({"[Program.cpp] Running as child."});
    Program::child = new Child();
    Program::child->prepare();
    Program::child->run();
  }
}

void Program::end(void) {

  if (Program::parent != nullptr) {
    Log::debug({"[Program.cpp] Ending parent."});
    Program::parent->end();
  }

  if (Program::child != nullptr) {
    Log::debug({"[Program.cpp] Ending child."});
    Program::child->end();
  }


}
