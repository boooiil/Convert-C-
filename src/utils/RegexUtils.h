#ifndef REGEX_UTILS
#define REGEX_UTILS

#include <regex>
#include <string>
#include <vector>

class RegexUtils {
 public:
  static bool isMatch(std::string, std::string);
  static bool isMatch(std::string, std::string,
                      std::regex_constants::syntax_option_type);

  static std::string getFirstMatch(std::string, std::string);
  static std::string getFirstMatch(std::string, std::string,
                                   std::regex_constants::syntax_option_type);

  static std::vector<std::string> getAllMatches(std::string, std::string);
  static std::vector<std::string> getAllMatches(
      std::string, std::string, std::regex_constants::syntax_option_type);
};

#endif  // !REGEX_UTILS
