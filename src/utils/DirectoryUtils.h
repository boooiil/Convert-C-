#ifndef DIRECTORY_UTILS_H
#define DIRECTORY_UTILS_H

#include <filesystem>
#include <string>
#include <vector>

class DirectoryUtils {
 public:
  static std::vector<std::filesystem::directory_entry> getFilesInCWD(void);
  static std::vector<std::filesystem::directory_entry> getFilesInCWDWithExt(
      std::string);
  static std::vector<std::filesystem::directory_entry> getFilesInCWDWithExt(
      std::vector<const char*>);
  static std::vector<std::filesystem::directory_entry> findFileInSubdir(
      std::string);
};

#endif  // !DIRECTORY_UTILS_H
