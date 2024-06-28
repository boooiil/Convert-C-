#include "Program.h"

Program::Program() {}
Program::~Program() {
  if (this->parent != nullptr) {
    delete this->parent;
  }

  if (this->child != nullptr) {
    delete this->child;
  }

  if (this->settings != nullptr) {
    delete this->settings;
  }
}

void Program::run(int argc, char* argv[]) {
  Program::settings = new Settings(argc, argv);
}
