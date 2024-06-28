#include "./TrimBetween.h"

#include "../../../utils/ListUtils.h"
#include "../../../utils/RegexUtils.h"

TrimBetween::TrimBetween(void) : VectorArgument<std::string>() {
  helpMessage = "Trim the video between two timestamps.";
}

TrimBetween::~TrimBetween(void) {}

void TrimBetween::parse(std::string provided) {
  std::vector<std::string> timestamps = ListUtils::splitv(provided, ",");

  if (timestamps.size() != 2) {
    errored = true;
    return;
  }

  bool first = RegexUtils::isMatch(
      timestamps[0], R"(\d+(?:\.\d+|\:\d{2}\:\d{2}(?:\.\d+)?|(?:ms|ns|us)?))",
      std::regex::icase);
  bool second = RegexUtils::isMatch(
      timestamps[1], R"(\d+(?:\.\d+|\:\d{2}\:\d{2}(?:\.\d+)?|(?:ms|ns|us)?))",
      std::regex::icase);

  if (first && second) {
    value = timestamps;
  } else {
    errored = true;
  }
}