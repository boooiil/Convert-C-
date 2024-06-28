#include "IsParent.h"

IsParent::IsParent(void) : FlagArgument() {
  value = false;
  helpMessage = "Toggle client mode (force JSON output).";
}

IsParent::~IsParent(void) {}

void IsParent::parse(std::string provided) {
  if (provided == "true") {
    value = true;
  } else {
    value = false;
  }
}

IsParent& IsParent::operator=(const bool& provided) {
  value = provided;
  return *this;
}
