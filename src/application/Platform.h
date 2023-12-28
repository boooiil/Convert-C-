#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include <unordered_map>

class Platform {
 public:
  Platform(void);
  ~Platform(void);
  enum OS { WINDOWS, LINUX, LINUX_LIKE, MAC, UNKNOWN };

  static std::string getValue(OS);

 private:
  static std::unordered_map<OS, std::string> osMap;
};

#endif  // !PLATFORM_H
