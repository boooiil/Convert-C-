#include "LoggingFormat.h"

#include <string>

#include "../../enums/LoggingOptions.h"
#include "../BaseArgument.h"

LoggingFormat::LoggingFormat(void)
    : BaseArgument<LoggingOptions::Options>("-lf", "--loggingformat",
                                            "Logging format",
                                            LoggingOptions::Options::DEFAULT) {
  value = LoggingOptions::DEFAULT;
  helpMessage = "Set the display logging format.";
}

LoggingFormat::~LoggingFormat(void) {}

void LoggingFormat::parse(std::string provided) {
  LoggingOptions::Options option = LoggingOptions::getKey(provided);

  if (option == LoggingOptions::INVALID) {
    this->setErrored(true);
    return;
  }

  value = option;
}

const std::string LoggingFormat::toString(void) const {
  return LoggingOptions::getValue(this->value);
}

const bool LoggingFormat::hasData(void) const {
  return this->value != LoggingOptions::DEFAULT;
}
