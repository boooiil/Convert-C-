#ifndef STRING_UTILS
#define STRING_UTILS

#include <regex>
#include <string>
#include <vector>

class StringUtils {
 public:
  static std::string truncateString(std::string);
  static std::string replaceAll(std::string, std::string, std::string);
  static std::string replaceAll(std::string, std::regex, std::string);
  static std::vector<std::string> split(std::string, std::string);
  static std::string toLowerCase(std::string str);
};

#endif  // !STRING_UTILS
