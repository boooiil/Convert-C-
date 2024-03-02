#include "./ParallelAmount.h"

ParallelAmount::ParallelAmount(void) : IntegerArgument() {
  value = 1;
  helpMessage = "Amount of parallel encoding processes.";
};
ParallelAmount::~ParallelAmount(void) {}

void ParallelAmount::parse(std::string provided) {
  try {
    value = std::stoi(provided);
  } catch (std::exception e) {
    errored = true;
  }
}