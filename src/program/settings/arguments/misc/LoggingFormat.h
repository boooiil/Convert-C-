#ifndef LOGGING_FORMAT_H
#define LOGGING_FORMAT_H

#include <string>

#include "../../enums/LoggingOptions.h"
#include "../../enums/StringEnumDataHolder.h"
#include "../BaseArgument.h"

class LoggingFormat
    : public BaseArgument<StringEnumDataHolder<LoggingOptions>> {
 public:
  LoggingFormat();
  ~LoggingFormat();

  /**
   * @brief Parse the start at argument.
   *
   * @param[in] argument - Argument.
   */
  void parse(std::string argument) override;

  const std::string toString(void) const override;
  const bool hasData(void) const override;
};

#endif  // !LOGGING_FORMAT_H
