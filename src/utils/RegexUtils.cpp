#include "RegexUtils.h"

/**
 * @brief Checks if a string matches a regex pattern
 *
 * @param str - string to be matched
 * @param pattern - regex pattern
 * @return true - if the string matches the pattern
 */
bool RegexUtils::isMatch(std::string str, std::string pattern) {
  std::regex regex(pattern);
  std::smatch match;

  return std::regex_search(str, match, regex);
}

/**
 * @brief Checks if a string matches a regex pattern
 *
 * @param str - string to be matched
 * @param pattern - regex pattern
 * @param flag - regex flag
 *
 * @return true - if the string matches the pattern
 */
bool RegexUtils::isMatch(std::string str, std::string pattern,
                         std::regex_constants::syntax_option_type flag) {
  std::regex regex(pattern, flag);
  std::smatch match;

  return std::regex_search(str, match, regex);
}

/**
 * @brief Get the first match of a string that matches a regex pattern
 *
 * @param str - string to be matched
 * @param pattern - regex pattern
 *
 * @return std::string - first match of the string
 */
std::string RegexUtils::getFirstMatch(std::string str, std::string pattern) {
  std::regex regex(pattern);
  std::smatch match;

  if (std::regex_search(str, match, regex)) {
    return match[1];
  } else
    return "";
}

/**
 * @brief Get the first match of a string that matches a regex pattern
 *
 * @param str - string to be matched
 * @param pattern - regex pattern
 * @param flag - regex flag
 *
 * @return std::string - first match of the string
 */
std::string RegexUtils::getFirstMatch(
    std::string str, std::string pattern,
    std::regex_constants::syntax_option_type flag) {
  std::regex regex(pattern, flag);
  std::smatch match;

  if (std::regex_search(str, match, regex)) {
    return match[1];
  } else
    return "";
}

/**
 * @brief Get all matches of a string that matches a regex pattern
 *
 * @param str - string to be matched
 * @param pattern - regex pattern
 *
 * @return std::vector<std::string> - all matches of the string
 */
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

/**
 * @brief Get all matches of a string that matches a regex pattern
 *
 * @param str - string to be matched
 * @param pattern - regex pattern
 * @param flag - regex flag
 *
 * @return std::vector<std::string> - all matches of the string
 */
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