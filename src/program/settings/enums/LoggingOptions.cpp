#include "LoggingOptions.h"

#include <string>
#include <unordered_map>
#include <utility>

#include "../../../utils/StringUtils.h"
#include "StringEnumDataHolder.h"
const StringEnumDataHolder<LoggingOptions> LoggingOptions::INVALID("invalid",
                                                                   "Invalid");

const StringEnumDataHolder<LoggingOptions> LoggingOptions::DEFAULT("default",
                                                                   "Default");
const StringEnumDataHolder<LoggingOptions> LoggingOptions::DEBUG("debug",
                                                                 "Debug");
const StringEnumDataHolder<LoggingOptions> LoggingOptions::VERBOSE("verbose",
                                                                   "Verbose");
const StringEnumDataHolder<LoggingOptions> LoggingOptions::JSON("json", "Json");
const StringEnumDataHolder<LoggingOptions> LoggingOptions::JSON_DEBUG(
    "json_debug", "JsonDebug");
const StringEnumDataHolder<LoggingOptions> LoggingOptions::JSON_VERBOSE(
    "json_verbose", "JsonVerbose");

bool LoggingOptions::isJSON(
    StringEnumDataHolder<LoggingOptions> providedOption) {
  return providedOption == LoggingOptions::JSON ||
         providedOption == LoggingOptions::JSON_DEBUG ||
         providedOption == LoggingOptions::JSON_VERBOSE;
}

bool LoggingOptions::isDebug(
    StringEnumDataHolder<LoggingOptions> providedOption) {
  return providedOption == LoggingOptions::DEBUG ||
         providedOption == LoggingOptions::JSON_DEBUG ||
         providedOption == LoggingOptions::VERBOSE ||
         providedOption == LoggingOptions::JSON_VERBOSE;
}

bool LoggingOptions::isVerbose(
    StringEnumDataHolder<LoggingOptions> providedOption) {
  return providedOption == LoggingOptions::VERBOSE ||
         providedOption == LoggingOptions::JSON_VERBOSE;
}
