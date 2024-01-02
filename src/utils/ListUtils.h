#ifndef LIST_UTILS_H
#define LIST_UTILS_H

#include <string>
#include <vector>

class ListUtils {
 public:
  static std::string join(std::vector<std::string> list,
                          std::string delim = "");
  static std::vector<std::string> splitv(std::string list,
                                         std::string delim = "");
};

#endif