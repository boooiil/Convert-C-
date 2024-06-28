#include "./Validate.h"

Validate::Validate(void) : FlagArgument() {
  value = true;
  helpMessage = "Toggle output validation.";
}

Validate::~Validate(void) {}

void Validate::parse(std::string provided) {
  if (provided != "true") {
    errored = true;
    return;
  }

  value = true;
}

Validate& Validate::operator=(const bool& provided) {
  value = provided;
  return *this;
}