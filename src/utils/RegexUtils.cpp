#include "RegexUtils.h"

bool RegexUtils::isMatch(std::string str, std::string pattern) {
  std::regex regex(pattern);
  std::smatch match;

  return std::regex_search(str, match, regex);
}

bool RegexUtils::isMatch(std::string str, std::string pattern,
  std::regex_constants::syntax_option_type flag) {
  std::regex regex(pattern, flag);
  std::smatch match;

  return std::regex_search(str, match, regex);
}

bool RegexUtils::isMatch(char c, std::string pattern) {
  std::string c_str(1, c);
  std::regex regex(pattern);
  std::smatch match;

  return std::regex_search(c_str, match, regex);
}

bool RegexUtils::isMatch(char c, std::string pattern,
  std::regex_constants::syntax_option_type flag) {
  std::string c_str(1, c);
  std::regex regex(pattern, flag);
  std::smatch match;

  return std::regex_search(c_str, match, regex);
}

bool RegexUtils::isMatch(char* c, std::string pattern) {
  std::string c_str(c);
  std::regex regex(pattern);
  std::smatch match;

  return std::regex_search(c_str, match, regex);
}

bool RegexUtils::isMatch(char* c, std::string pattern,
  std::regex_constants::syntax_option_type flag) {
  std::string c_str(c);
  std::regex regex(pattern, flag);
  std::smatch match;

  return std::regex_search(c_str, match, regex);
}

std::string RegexUtils::getFirstMatch(std::string str, std::string pattern) {
  std::regex regex(pattern);
  std::smatch match;

  if (std::regex_search(str, match, regex)) {
    return match[1];
  }
  else
    return "";
}

std::string RegexUtils::getFirstMatch(
  std::string str, std::string pattern,
  std::regex_constants::syntax_option_type flag) {
  std::regex regex(pattern, flag);
  std::smatch match;

  if (std::regex_search(str, match, regex)) {
    return match[1];
  }
  else
    return "";
}

std::vector<std::string> RegexUtils::getAllMatches(std::string str,
  std::string pattern) {
  std::regex regex(pattern);
  std::smatch match;
  std::vector<std::string> matches;

  while (std::regex_search(str, match, regex)) {
    matches.push_back(match[0]);
    str = match.suffix().str();
  }

  return matches;
}

std::vector<std::string> RegexUtils::getAllMatches(
  std::string str, std::string pattern,
  std::regex_constants::syntax_option_type flag) {
  std::regex regex(pattern, flag);
  std::smatch match;
  std::vector<std::string> matches;

  while (std::regex_search(str, match, regex)) {
    for (int i = 1; i < match.size(); i++) {
      matches.push_back(match[i]);
    }

    str = match.suffix().str();
  }

  return matches;
}

std::regex RegexUtils::createRegex(std::string pattern, std::regex_constants::syntax_option_type flag) {
  return std::regex(pattern, flag);
}