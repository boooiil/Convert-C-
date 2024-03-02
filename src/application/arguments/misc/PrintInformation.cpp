#include "./PrintInformation.h"

PrintInformation::PrintInformation(void) : FlagArgument() {
  helpMessage = "Prints the information message.";
}

PrintInformation::~PrintInformation(void) {}

void PrintInformation::parse(std::string provided) {
  if (provided != "true") {
    errored = true;
    return;
  }

  value = true;
}

PrintInformation& PrintInformation::operator=(const bool& provided) {
  value = provided;
  return *this;
}