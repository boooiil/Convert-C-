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

std::vector<std::string> ListUtils::splitv(std::string str, std::string delim) {
  std::vector<std::string> result;
  std::string token;
  size_t pos = 0;
  while ((pos = str.find(delim)) != std::string::npos) {
    token = str.substr(0, pos);
    result.push_back(token);
    str.erase(0, pos + delim.length());
  }
  result.push_back(str);
  return result;
}