#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <nlohmann/json_fwd.hpp>
#include <string>

#include "../arguments/encoding/DesiredEncoder.h"
#include "../arguments/misc/LoggingFormat.h"
#include "../arguments/video/Quality.h"
#include "../enums/Tunes.h"

class ArgumentParser {
 public:
  ArgumentParser(void);
  ~ArgumentParser(void);

  /// @brief The current encoder being used
  Quality quality;
  /// @brief Codec tune setting
  Tunes::Tune tune;
  /// @brief The user's desired encoder
  DesiredEncoder wantedEncoder;

  LoggingFormat loggingFormat;

  void prepare(void);
  void parse(int argc, char* argv[]);
  void invalidArgument(std::string);

  nlohmann::json asJSON(void);
};

#endif  // !ARGUMENT_PARSER_H
