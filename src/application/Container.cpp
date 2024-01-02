#include "Container.h"

#include <filesystem>

#include "../logging/Log.h"

Container::Container() {}
Container::~Container() {}

void Container::scanWorkingDir() {
  namespace fs = std::filesystem;

  fs::path start_dir = fs::current_path();

  Container::log.debug(
      {"[Container.cpp] Scanning directory:", start_dir.generic_string()});

  for (const auto& entry : fs::directory_iterator(start_dir)) {
    if (entry.is_regular_file()) {
      if (entry.path().extension() == ".mkv") {
        Container::log.debug({"[Container.cpp] Found file:",
                              entry.path().filename().generic_string()});

        Media media = Media(entry.path().filename().generic_string(),
                            Container::settings.workingDir);
        media.rename(*this);

        // if series folder doesn't exist, create it
        if (!fs::exists(Container::settings.workingDir + "/" +
                        media.file.series + " Season " +
                        std::to_string(media.file.season))) {
          Container::log.debug(
              {"[Container.cpp] Series folder does not exist for series:",
               media.file.series});
          // create directory
          Container::log.debug({"[Container.cpp] Creating directory:",
                                Container::settings.workingDir + "/" +
                                    media.file.series + " Season " +
                                    std::to_string(media.file.season)});

          fs::create_directory(Container::settings.workingDir + "/" +
                               media.file.series + " Season " +
                               std::to_string(media.file.season));
        }

        // log.sendPlain({"Media conversion name:", media.file.conversionName});
        // log.sendPlain({"Media conversion path:", media.file.conversionPath});
        // log.sendPlain({"Media episode:", media.file.episode});
        // log.sendPlain({"Media ext:", media.file.ext});
        // log.sendPlain(
        //     {"Media modified file name:", media.file.modifiedFileName});
        // log.sendPlain(
        //     {"Media modified file name ext:",
        //     media.file.modifiedFileNameExt});
        // log.sendPlain({"Media rename path:", media.file.renamePath});
        // log.sendPlain({"Media season:", std::to_string(media.file.season)});
        // log.sendPlain({"Media series:", media.file.series});
        // log.sendPlain({"Media quality:",
        // std::to_string(media.file.quality)});

        Container::pending.push(media);
      }
    }
  }
}