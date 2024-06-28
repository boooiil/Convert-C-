#include "LoggingOptions.h"

#include "../../utils/StringUtils.h"

std::unordered_map<LoggingOptions::Options, std::string>
    LoggingOptions::loggingOptionMap = {
        {LoggingOptions::Options::DEFAULT, "default"},
        {LoggingOptions::Options::DEBUG, "debug"},
        {LoggingOptions::Options::VERBOSE, "verbose"},
        {LoggingOptions::Options::JSON, "json"},
        {LoggingOptions::Options::JSON_DEBUG, "json_debug"},
        {LoggingOptions::Options::JSON_VERBOSE, "json_verbose"},
        {LoggingOptions::INVALID, "invalid"}};

LoggingOptions::LoggingOptions(void) {}
LoggingOptions::~LoggingOptions(void) {}

LoggingOptions::Options LoggingOptions::getKey(std::string providedOption) {
  for (std::pair<LoggingOptions::Options, std::string> loggingOption :
       loggingOptionMap) {
    std::string value = StringUtils::toLowerCase(loggingOption.second);
    if (value == providedOption) {
      return loggingOption.first;
    }
  }

  return LoggingOptions::Options::INVALID;
}

std::string LoggingOptions::getValue(LoggingOptions::Options providedOption) {
  return loggingOptionMap[providedOption];
}

bool LoggingOptions::isJSON(LoggingOptions::Options providedOption) {
  return providedOption == LoggingOptions::Options::JSON ||
         providedOption == LoggingOptions::Options::JSON_DEBUG ||
         providedOption == LoggingOptions::Options::JSON_VERBOSE;
}

bool LoggingOptions::isDebug(LoggingOptions::Options providedOption) {
  return providedOption == LoggingOptions::Options::DEBUG ||
         providedOption == LoggingOptions::Options::JSON_DEBUG ||
         providedOption == LoggingOptions::Options::VERBOSE ||
         providedOption == LoggingOptions::Options::JSON_VERBOSE;
}

bool LoggingOptions::isVerbose(LoggingOptions::Options providedOption) {
  return providedOption == LoggingOptions::Options::VERBOSE ||
         providedOption == LoggingOptions::Options::JSON_VERBOSE;
}
