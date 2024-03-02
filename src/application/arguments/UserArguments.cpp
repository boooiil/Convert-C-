#include "UserArguments.h"

#include "../../logging/LogColor.h"
#include "../../media/MediaDefinedFormat.h"
#include "../../utils/ListUtils.h"
#include "../../utils/RegexUtils.h"
#include "../../utils/StringUtils.h"
#include "../Container.h"
#include "../Ticker.h"
#include "./encoding/AudioStreamIndexes.h"

UserArguments::UserArguments() {}
UserArguments::~UserArguments() {}

void UserArguments::parse(Container* container, int argc, char* argv[]) {
  if (argc == 1) {
    // todo: send help message
    return UserArguments::invalidArgument(container, "No arguments provided.");
  }

  for (int i = 1; i < argc; i++) {
    Log::debug({"[UserArguments.cpp] Option:", argv[i]});
    std::string option = StringUtils::toLowerCase(argv[i]);

    // yandere dev moment

    if (option == "-as" || option == "--audiostreams") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }

      container->userSettings.audioStreams.parse(argv[++i]);

      if (container->userSettings.audioStreams.errored) {
        return invalidArgument(container, "Invalid audio stream indexes.");
      }
    }

    else if (option == "-h" || option == "--help") {
      container->userSettings.printHelp = true;
    }

    else if (option == "-i" || option == "--info") {
      container->userSettings.printInformation = true;
    }

    else if (option == "-d" || option == "--debug") {
      container->userSettings.debug = true;
    }

    else if (option == "-e" || option == "--encoder") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }

      container->userSettings.wantedEncoder.parse(argv[++i]);

      if (container->userSettings.wantedEncoder.errored) {
        return invalidArgument(container, "Invalid encoder provided.");
      }

    }

    else if (option == "-q" || option == "quality") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }

      container->userSettings.quality.parse(argv[++i]);

      if (container->userSettings.quality.errored) {
        return invalidArgument(container, "Invalid quality provided.");
      }

    }

    else if (option == "-t" || option == "--tune") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }

      Tunes::Tune tune = Tunes::getKey(argv[++i]);

      if (tune == Tunes::DEFAULT) {
        return invalidArgument(container, "Invalid tune provided.");
      }

      container->userSettings.tune = tune;
    }

    else if (option == "-a" || option == "--amount") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }

      container->userSettings.amount.parse(argv[++i]);

      if (container->userSettings.amount.errored) {
        return invalidArgument(container, "Invalid amount provided.");
      }

    }

    else if (option == "-c" || option == "--crop") {
      container->userSettings.crop = true;
    }

    else if (option == "-s" || option == "--start") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }

      container->userSettings.startBeginning.parse(argv[++i]);

      if (container->userSettings.startBeginning.errored) {
        return invalidArgument(container, "Invalid start time provided.");
      }
    }

    else if (option == "-tr" || option == "--trim") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }

      container->userSettings.trim.parse(argv[++i]);

      if (container->userSettings.trim.errored) {
        return invalidArgument(container, "Invalid trim times provided.");
      }
    }

    else if (option == "-b" || option == "--bitrate") {
      container->userSettings.useBitrate = true;
    }

    else if (option == "-co" || option == "--constrain") {
      container->userSettings.useConstrain = true;
    }

    else if (option == "-crf" || option == "--crf") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }

      container->userSettings.crfOverride.parse(argv[++i]);

      if (container->userSettings.crfOverride.errored) {
        return invalidArgument(container, "Invalid crf value provided.");
      }
    }

    else if (option == "-hwe" || option == "hardwareencode") {
      container->userSettings.useHardwareEncode = true;
    }

    else if (option == "-hwd" || option == "hardwaredecode") {
      container->userSettings.useHardwareDecode = true;
    }

    else if (option == "-o" || option == "--overwrite") {
      container->userSettings.overwrite = true;
    }

    else {
      invalidArgument(container, argv[i]);
    }
  }
}

void UserArguments::invalidArgument(Container* container, const char* arg) {
  Log::send({LogColor::fgRed(arg)});
}