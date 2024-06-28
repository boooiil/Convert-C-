#include "./UseHardwareEncode.h"

UseHardwareEncode::UseHardwareEncode() : FlagArgument() {
  value = false;
  helpMessage = "Use hardware encoding.";
}

UseHardwareEncode::~UseHardwareEncode() {}

void UseHardwareEncode::parse(std::string provided) {
  if (provided == "true" || provided == "false") {
    value = provided == "true";
  } else {
    errored = true;
  }
}

UseHardwareEncode& UseHardwareEncode::operator=(const bool& provided) {
  value = provided;
  return *this;
}