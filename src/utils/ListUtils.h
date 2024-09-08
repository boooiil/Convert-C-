/*********************************************************************
 * @file   ListUtils.h
 * @brief  List utilities header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef LIST_UTILS_H
#define LIST_UTILS_H

#include <exception>
#include <regex>
#include <string>
#include <vector>

#include "../logging/Log.h"

/**
 * @brief Handle various functions that involve list-like data structures.
 */
class ListUtils {
 public:
  /**
   * @brief Join a list of strings.
   *
   * @param[in] list  - The list of strings.
   * @param[in] delim - The delimiter to join the strings with.
   * @return The joined string.
   */
  static std::string join(std::vector<std::string> list,
                          std::string delim = "");

  /**
   * @brief Split a string into a vector of strings.
   *
   * @param[in] str   - The string to split.
   * @param[in] delim - The delimiter to split the string with.
   * @return A list of strings.
   */
  static std::vector<std::string> splitv(std::string str,
                                         std::string delim = "");

  static std::vector<std::string> splitv(std::string str, std::regex);

  template <typename T>
  static bool contains(std::vector<T> list, T item) {
    for (T listItem : list) {
      try {
        if (listItem == item) {
          return true;
        }
      } catch (std::exception e) {
        Log::debug({"[ListUtils.h] Error: ", e.what()});
        continue;
      }
    }
    return false;
  }
};

#endif