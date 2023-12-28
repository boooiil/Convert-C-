#ifndef STRING_UTILS
#define STRING_UTILS

#include <regex>
#include <string>

class StringUtils {
 public:
  static std::string truncateString(std::string);
  static std::string replaceAll(std::string, std::string, std::string);
  static std::string replaceAll(std::string, std::regex, std::string);
  static std::string toLowerCase(std::string str);
};

#endif  // !STRING_UTILS
