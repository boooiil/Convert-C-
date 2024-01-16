#include "Container.h"

#include <filesystem>

#include "../logging/Log.h"

Container::Container() {}
Container::~Container() {
  this->log.debug({"[Container.cpp] deconstructing Container"});
  this->log.debug({"[Container.cpp] converting size:",
                   std::to_string(Container::converting.size())});
  this->log.debug({"[Container.cpp] pending size:",
                   std::to_string(Container::pending.size())});

  while (!Container::converting.empty()) {
    Media* media = Container::converting.front();
    this->log.debug(
        {"[Container.cpp] Deleting media file:", media->file->conversionName});
    Container::converting.pop();
    delete media;
  }

  while (!Container::pending.empty()) {
    Media* media = Container::pending.front();
    this->log.debug(
        {"[Container.cpp] Deleting media file:", media->file->conversionName});
    Container::pending.pop();
    delete media;
  }

  this->log.debug({"[Container.cpp] converting size after:",
                   std::to_string(Container::converting.size())});
  this->log.debug({"[Container.cpp] pending size after:",
                   std::to_string(Container::pending.size())});
}

void Container::scanWorkingDir() {
  namespace fs = std::filesystem;

  fs::path start_dir = fs::current_path();

  Container::log.debug(
      {"[Container.cpp] Scanning directory:", start_dir.generic_string()});

  for (const auto& entry : fs::directory_iterator(start_dir)) {
    if (entry.is_regular_file()) {
      if (entry.path().extension() == ".mkv") {
        Log::debug({"[Container.cpp] Found file:",
                    entry.path().filename().generic_string()});

        Media* media = new Media(entry.path().filename().generic_string(),
                                 Container::settings.workingDir);
        media->file->rename();

        // if series folder doesn't exist, create it
        if (!fs::exists(Container::settings.workingDir + "/" +
                        media->file->series + " Season " +
                        std::to_string(media->file->season))) {
          Log::debug(
              {"[Container.cpp] Series folder does not exist for series:",
               media->file->series});
          // create directory
          Log::debug({"[Container.cpp] Creating directory:",
                      Container::settings.workingDir + "/" +
                          media->file->series + " Season " +
                          std::to_string(media->file->season)});

          fs::create_directory(Container::settings.workingDir + "/" +
                               media->file->series + " Season " +
                               std::to_string(media->file->season));
        }

        this->pending.push(media);
      }
    }
  }
}