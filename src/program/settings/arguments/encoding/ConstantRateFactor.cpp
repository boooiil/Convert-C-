#include "./ConstantRateFactor.h"

#include <exception>
#include <string>

#include "../../../../logging/Log.h"
#include "../IntegerArgument.h"

ConstantRateFactor::ConstantRateFactor() : IntegerArgument() {
  value = -1;
  helpMessage = "Constant rate factor for encoding.";
}

ConstantRateFactor::~ConstantRateFactor() {}

void ConstantRateFactor::parse(std::string provided) {
  try {
    value = std::stoi(provided);
  } catch (std::exception& e) {
    Log::debug({"Failed to parse crf: ", provided, "\n", e.what()});
    errored = true;
  }
}