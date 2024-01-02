#include "ListUtils.h"

std::string ListUtils::join(std::vector<std::string> list, std::string delim) {
  std::string result = "";
  for (int i = 0; i < list.size(); i++) {
    result += list[i];
    if (i < list.size() - 1) {
      result += delim;
    }
  }
  return result;
}