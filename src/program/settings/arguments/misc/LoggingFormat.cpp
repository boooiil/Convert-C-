#include "LoggingFormat.h"

LoggingFormat::LoggingFormat(void) : BaseArgument<LoggingOptions::Options>() {
  value = LoggingOptions::DEFAULT;
  helpMessage = "Set the display logging format.";
}

LoggingFormat::~LoggingFormat(void) {}

void LoggingFormat::parse(std::string provided) {
  LoggingOptions::Options option = LoggingOptions::getKey(provided);

  if (option == LoggingOptions::INVALID) {
    errored = true;
    return;
  }

  value = option;
}
