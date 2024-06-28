#ifndef LOGGING_OPTIONS_H
#define LOGGING_OPTIONS_H

#include <string>
#include <unordered_map>

class LoggingOptions {
 public:
  LoggingOptions(void);
  ~LoggingOptions(void);

  enum Options {
    DEFAULT,
    DEBUG,
    VERBOSE,
    JSON,
    JSON_DEBUG,
    JSON_VERBOSE,
    INVALID
  };

  /**
   * @brief Get the codec from a string.
   *
   * @param[in] providedOption - Desired logging option.
   *
   * @return Codec enum.
   */
  static Options getKey(std::string providedOption);

  /**
   * @brief Get the string value of the enum.
   *
   * @param[in] providedOption - Desired logging option.
   *
   * @return String value of enum.
   */
  static std::string getValue(Options providedOption);

  /**
   * @brief Check if the provided option is JSON.
   *
   * @param[in] providedOption - Desired logging option.
   * @return True if JSON, false otherwise.
   */
  static bool isJSON(Options providedOption);

  /**
   * @brief Check if the provided option is Debug.
   *
   * @param[in] providedOption - Desired logging option.
   * @return True if Debug, false otherwise.
   */
  static bool isDebug(Options providedOption);

  /**
   * @brief Check if the provided option is Verbose.
   *   *
   * @param[in] providedOption - Desired logging option.
   *   * @return True if Verbose, false otherwise.
   */
  static bool isVerbose(Options providedOption);

 private:
  static std::unordered_map<Options, std::string> loggingOptionMap;
};

#endif  // LOGGING_OPTIONS_H
