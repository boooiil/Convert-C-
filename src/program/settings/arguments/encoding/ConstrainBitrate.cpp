#include "./ConstrainBitrate.h"

ConstrainBitrate::ConstrainBitrate() : FlagArgument() {
  value = false;
  helpMessage = "Constrain bitrate for encoding.";
}

ConstrainBitrate::~ConstrainBitrate() {}

void ConstrainBitrate::parse(std::string provided) {
  if (provided == "true" || provided == "false") {
    value = provided == "true";
  } else {
    errored = true;
  }
}

ConstrainBitrate& ConstrainBitrate::operator=(const bool& provided) {
  value = provided;
  return *this;
}