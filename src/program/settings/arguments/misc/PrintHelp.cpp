#include "./PrintHelp.h"

PrintHelp::PrintHelp(void) : FlagArgument() {
  helpMessage = "Prints the help message.";
}

PrintHelp::~PrintHelp(void) {}

void PrintHelp::parse(std::string provided) {
  if (provided != "true") {
    errored = true;
    return;
  }

  value = true;
}

PrintHelp& PrintHelp::operator=(const bool& provided) {
  value = provided;
  return *this;
}