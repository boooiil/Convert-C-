#ifndef LOGGING_FORMAT_H
#define LOGGING_FORMAT_H

#include <string>

#include "../../settings/LoggingOptions.h"
#include "../BaseArgument.h"

class LoggingFormat : public BaseArgument<LoggingOptions::Options> {
 public:
  LoggingFormat();
  ~LoggingFormat();

  /**
   * @brief Parse the start at argument.
   *
   * @param[in] argument - Argument.
   */
  void parse(std::string argument) override;
};

#endif  // !LOGGING_FORMAT_H
