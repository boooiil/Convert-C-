#include "./Crop.h"

Crop::Crop(void) : FlagArgument() {
  value = false;
  helpMessage = "Crop the video.";
}

Crop::~Crop(void) {}

void Crop::parse(std::string provided) {
  if (provided == "true") {
    value = true;
  } else if (provided == "false") {
    value = false;
  } else {
    errored = true;
  }
}

Crop& Crop::operator=(const bool& provided) {
  value = provided;
  return *this;
}