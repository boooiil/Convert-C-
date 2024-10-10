#ifndef STRING_ENUM_DATA_HOLDER_H
#define STRING_ENUM_DATA_HOLDER_H

#include <string>

template <typename Binder>
class StringEnumDataHolder {
 public:
  StringEnumDataHolder(std::string _name, std::string _description)
      : name(_name), description(_description) {}

  std::string getName() const { return name; }

  // Overload the equality operator for comparison
  bool operator==(const StringEnumDataHolder& other) const {
    return name == other.name;
  }

  bool operator!=(const StringEnumDataHolder& other) const {
    return name != other.name;
  }

  std::string operator+(const std::string& other) const { return name + other; }

  operator std::string const(void) { return name; }

 private:
  std::string name;
  std::string description;
};

#endif  // STRING_ENUM_DATA_HOLDER_H