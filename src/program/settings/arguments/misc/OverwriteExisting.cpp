#include "./OverwriteExisting.h"

OverwriteExisting::OverwriteExisting() : FlagArgument() {
  value = false;
  helpMessage = "Overwrite existing files.";
}

OverwriteExisting::~OverwriteExisting() {}

void OverwriteExisting::parse(std::string provided) {
  if (provided == "true" || provided == "false") {
    value = provided == "true";
  } else {
    errored = true;
  }
}

OverwriteExisting& OverwriteExisting::operator=(const bool& provided) {
  value = provided;
  return *this;
}