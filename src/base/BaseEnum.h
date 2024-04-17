#ifndef BASE_ENUM_H
#define BASE_ENUM_H

#include <unordered_map>

template <typename T>
class BaseEnum {
 public:
  std::string getValue(T key) { return enumMap[key]; };

  T getKey(std::string value) {
    for (auto it = enumMap.begin(); it != enumMap.end(); ++it) {
      if (it->second == value) {
        return it->first;
      }
    }
    return T();
  };

 private:
  std::unordered_map<T, std::string> enumMap;
};

#endif  // BASE_ENUM_H