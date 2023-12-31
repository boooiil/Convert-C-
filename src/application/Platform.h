#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include <unordered_map>

class Platform {
 public:
  Platform(void);
  ~Platform(void);
  enum OPERATING_SYSTEM { WINDOWS, _LINUX, LINUX_LIKE, MAC, UNKNOWN };

  static std::string getValue(OPERATING_SYSTEM);

 private:
  static std::unordered_map<OPERATING_SYSTEM, std::string> osMap;
};

#endif  // !PLATFORM_H
