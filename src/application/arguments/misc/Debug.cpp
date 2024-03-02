#include "./Debug.h"

Debug::Debug(void) : FlagArgument() {
  value = false;
  helpMessage = "Enable debug mode.";
}

Debug::~Debug(void) {}

void Debug::parse(std::string provided) {
  if (provided == "true") {
    value = true;
  } else if (provided == "false") {
    value = false;
  } else {
    errored = true;
  }
}

Debug& Debug::operator=(const bool& provided) {
  value = provided;
  return *this;
}