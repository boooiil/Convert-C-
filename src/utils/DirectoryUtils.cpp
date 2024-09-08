#include "DirectoryUtils.h"

#include <filesystem>
#include <string>
#include <vector>
#include "../logging/Log.h"
#include "ListUtils.h"

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

bool DirectoryUtils::createDir(std::string path) {
  if (std::filesystem::exists(path)) {
    return true;
  }

  try {
    std::filesystem::create_directory(path);
    return true;
  }
  catch (std::exception err) {
    Log::debug({ err.what() });
    return false;
  }
}

bool DirectoryUtils::createDir(std::string path, bool recursive) {

  if (!recursive) {
    return createDir(path);
  }

  std::vector<std::string> paths = ListUtils::splitv(path, std::regex(R"(\|/)"));
  std::string built_path;

  for (std::string dir : paths) {
    if (!createDir(built_path)) {
      return false;
    }
    // can use std::filesystem::preferred_separator
    built_path += dir + "/";
  }

  return true;

}