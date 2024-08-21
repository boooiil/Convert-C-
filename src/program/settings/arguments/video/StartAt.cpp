#include "./StartAt.h"

#include <regex>
#include <string>

#include "../../../../utils/RegexUtils.h"
#include "../StringArgument.h"

StartAt::StartAt() : StringArgument() {
  value = "";
  helpMessage = "Start the video at a specific time.";
}

StartAt::~StartAt() {}

void StartAt::parse(std::string provided) {
  if (RegexUtils::isMatch(
          provided, R"(\d+(?:\.\d+|\:\d{2}\:\d{2}(?:\.\d+)?|(?:ms|ns|us)?))",
          std::regex::icase)) {
    value = provided;
  } else {
    errored = true;
  }
}
