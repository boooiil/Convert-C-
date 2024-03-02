#include "./UseHardwareDecode.h"

UseHardwareDecode::UseHardwareDecode() : FlagArgument() {
  value = true;
  helpMessage = "Use hardware decode for encoding.";
}

UseHardwareDecode::~UseHardwareDecode() {}

void UseHardwareDecode::parse(std::string provided) {
  if (provided == "true" || provided == "false") {
    value = provided == "true";
  } else {
    errored = true;
  }
}

UseHardwareDecode& UseHardwareDecode::operator=(const bool& provided) {
  value = provided;
  return *this;
}