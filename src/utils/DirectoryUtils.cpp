#include "DirectoryUtils.h"

#include <filesystem>
#include <string>
#include <vector>

std::vector<std::filesystem::directory_entry> DirectoryUtils::getFilesInCWD() {
  std::vector<std::filesystem::directory_entry> files;
  for (const auto& entry :
       std::filesystem::directory_iterator(std::filesystem::current_path())) {
    if (entry.is_regular_file()) {
      files.push_back(entry);
    }
  }
  return files;
}

std::vector<std::filesystem::directory_entry>
DirectoryUtils::getFilesInCWDWithExt(std::string ext) {
  std::vector<std::filesystem::directory_entry> files;
  for (const auto& entry :
       std::filesystem::directory_iterator(std::filesystem::current_path())) {
    if (entry.is_regular_file() && entry.path().extension() == ext) {
      files.push_back(entry);
    }
  }
  return files;
}

std::vector<std::filesystem::directory_entry>
DirectoryUtils::getFilesInCWDWithExt(std::vector<const char*> exts) {
  std::vector<std::filesystem::directory_entry> files;
  for (const auto& entry :
       std::filesystem::directory_iterator(std::filesystem::current_path())) {
    if (entry.is_regular_file()) {
      for (std::string ext : exts) {
        if (entry.path().extension() == ext) {
          files.push_back(entry);
        }
      }
    }
  }

  return files;
}

std::vector<std::filesystem::directory_entry> DirectoryUtils::findFileInSubdir(
    std::string filename) {
  std::vector<std::filesystem::directory_entry> files;
  for (const auto& entry : std::filesystem::recursive_directory_iterator(
           std::filesystem::current_path())) {
    if (entry.is_regular_file() && entry.path().filename() == filename) {
      files.push_back(entry);
    }
  }
  return files;
}
