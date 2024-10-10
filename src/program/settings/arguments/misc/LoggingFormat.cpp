#include "LoggingFormat.h"

#include <string>

#include "../../enums/LoggingOptions.h"
#include "../../enums/StringEnumDataHolder.h"
#include "../BaseArgument.h"

LoggingFormat::LoggingFormat(void)
    : BaseArgument<StringEnumDataHolder<LoggingOptions>>(
          "-lf", "--loggingformat", "Logging format", LoggingOptions::DEFAULT) {
  value = LoggingOptions::DEFAULT;
  helpMessage = "Set the display logging format.";
}

LoggingFormat::~LoggingFormat(void) {}

void LoggingFormat::parse(std::string provided) {
  StringEnumDataHolder<LoggingOptions> option =
      LoggingOptions::getKey(provided);

  if (option == LoggingOptions::INVALID) {
    this->setErrored(true);
    return;
  }

  value = option;
}

const std::string LoggingFormat::toString(void) const {
  return this->value.getName();
}

const bool LoggingFormat::hasData(void) const {
  return this->value != LoggingOptions::DEFAULT;
}
