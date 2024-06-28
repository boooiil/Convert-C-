#include "./UseBitrate.h"

UseBitrate::UseBitrate() : FlagArgument() {
  value = false;
  helpMessage = "Use bitrate for encoding.";
}

UseBitrate::~UseBitrate() {}

void UseBitrate::parse(std::string provided) {
  if (provided == "true" || provided == "false") {
    value = provided == "true";
  } else {
    errored = true;
  }
}

UseBitrate& UseBitrate::operator=(const bool& provided) {
  value = provided;
  return *this;
}