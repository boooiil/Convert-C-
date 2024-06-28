/*********************************************************************
 * @file   Platform.h
 * @brief  Platform class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include <unordered_map>

/**
 * @brief Holds platform specific information.
 */
class Platform {
 public:
  Platform(void);
  ~Platform(void);

  /// @brief Enumerates the supported operating systems.
  enum OPERATING_SYSTEM { WINDOWS, _LINUX, LINUX_LIKE, MAC, UNKNOWN };

  /**
   * @brief Get the string value of the operating system.
   *
   * @param[in] os - The operating system.
   * @return The string value of the operating system.
   */
  static std::string getValue(OPERATING_SYSTEM os);

 private:
  /// @brief Map of operating system names and enum value.
  static std::unordered_map<OPERATING_SYSTEM, std::string> osMap;
};

#endif  // !PLATFORM_H
