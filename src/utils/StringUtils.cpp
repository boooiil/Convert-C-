#include "StringUtils.h"

#include <math.h>

#include <regex>
#include <string>

std::string StringUtils::truncateString(std::string str, int length = 25) {
  const int MAX_LENGTH = length;
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

std::string StringUtils::toLowerCase(std::string str) {
  const int x = 32;

  std::string result;

  for (char c : str) {
    if (c >= 65 && c <= 90) {
      result += static_cast<char>(c + x);
    } else {
      result += c;
    };
  }

  return result;
}

std::string StringUtils::toUpperCase(std::string str) {
  const int x = 32;

  std::string result;

  for (char c : str) {
    if (c >= 97 && c <= 122) {
      result += static_cast<char>(c - x);
    } else {
      result += c;
    };
  }

  return result;
}

bool StringUtils::contains(std::string str, std::string pattern) {
  return str.find(pattern) != std::string::npos;
}