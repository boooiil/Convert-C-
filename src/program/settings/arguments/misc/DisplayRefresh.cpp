#include "./DisplayRefresh.h"

#include "../IntegerArgument.h"

DisplayRefresh::DisplayRefresh(void) : IntegerArgument() {
  value = 1000;
  helpMessage = "Refresh rate of the display in milliseconds.";
};

DisplayRefresh::~DisplayRefresh(void) {}

void DisplayRefresh::parse(std::string provided) {
  try {
    value = std::stoi(provided);
  } catch (std::exception e) {
    errored = true;
  }
}
