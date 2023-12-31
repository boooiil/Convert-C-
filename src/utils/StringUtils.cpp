#include "StringUtils.h"

#include <cmath>

std::string StringUtils::truncateString(std::string str) {
  const int MAX_LENGTH = 10;
  if (str.length() <= MAX_LENGTH) {
    return str;
  }

  const std::string ellipsis = "... ";

  const int leftHalfLength =
      static_cast<int>(ceil((MAX_LENGTH - ellipsis.length()) / 2.0));
  const int rightHalfLength =
      static_cast<int>(floor((MAX_LENGTH - ellipsis.length()) / 2.0));

  const std::string leftHalf = str.substr(0, leftHalfLength);
  const std::string rightHalf = str.substr(str.length() - rightHalfLength);

  return leftHalf + ellipsis + rightHalf;

  // TODO: test this
}

std::string StringUtils::replaceAll(std::string str, std::string from,
                                    std::string to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos +=
        to.length();  // Handles case where 'to' is a substring of 'from'
  }

  return str;
}

std::string StringUtils::replaceAll(std::string str, std::regex from,
                                    std::string to) {
  return std::regex_replace(str, from, to);
}

std::vector<std::string> StringUtils::split(std::string str,
                                            std::string delim) {
  std::vector<std::string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == std::string::npos) pos = str.length();
    std::string token = str.substr(prev, pos - prev);
    if (!token.empty()) tokens.push_back(token);
    prev = pos + delim.length();
  } while (pos < str.length() && prev < str.length());

  return tokens;
}

std::string StringUtils::toLowerCase(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}