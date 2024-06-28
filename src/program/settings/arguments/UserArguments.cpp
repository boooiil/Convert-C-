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
    return invalidArgument("No arguments provided.");
  }

  for (int i = 1; i < argc; i++) {
    Log::debug({"[UserArguments.cpp] Option:", argv[i]});
    std::string option = StringUtils::toLowerCase(argv[i]);

    // yandere dev moment
    if (option == "-a" || option == "--amount") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      container->userSettings.amount.parse(argv[++i]);

      if (container->userSettings.amount.errored) {
        return invalidArgument("Invalid amount provided.");
      }
    }

    else if (option == "-as" || option == "--audiostreams") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      container->userSettings.audioStreams.parse(argv[++i]);

      if (container->userSettings.audioStreams.errored) {
        return invalidArgument("Invalid audio stream indexes.");
      }
    }

    else if (option == "-b" || option == "--bitrate") {
      container->userSettings.useBitrate = true;
    }

    else if (option == "-c" || option == "--crop") {
      container->userSettings.crop = true;
    }

    else if (option == "-parent") {
      container->userSettings.isParent = true;
    }

    else if (option == "-co" || option == "--constrain") {
      container->userSettings.useConstrain = true;
    }

    else if (option == "-crf" || option == "--crf") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      container->userSettings.crfOverride.parse(argv[++i]);

      if (container->userSettings.crfOverride.errored) {
        return invalidArgument("Invalid crf value provided.");
      }
    }

    else if (option == "-e" || option == "--encoder") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      container->userSettings.wantedEncoder.parse(argv[++i]);

      if (container->userSettings.wantedEncoder.errored) {
        return invalidArgument("Invalid encoder provided.");
      }

    }

    else if (option == "-h" || option == "--help") {
      container->userSettings.printHelp = true;
    }

    else if (option == "-hwe" || option == "hardwareencode") {
      container->userSettings.useHardwareEncode = true;
    }

    else if (option == "-hwd" || option == "hardwaredecode") {
      container->userSettings.useHardwareDecode = true;
    }

    else if (option == "-i" || option == "--info") {
      container->userSettings.printInformation = true;
    }

    else if (option == "-lf" || option == "--loggingformat") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      // TODO: this function logic is not like the others
      // we might have to check multiple variants of the argument
      // i'd like to revisit this later, but for now, it's fine

      // if debug and json are provided, set to json_debug
      // if json is provided, set to json

      // nevermind, we will move away from explicit debug
      // and just use the logging format to determine the output

      container->userSettings.loggingFormat.parse(argv[++i]);

      if (container->userSettings.loggingFormat.errored) {
        return invalidArgument("Invalid logging format provided.");
      }

    }

    else if (option == "-o" || option == "--overwrite") {
      container->userSettings.overwrite = true;
    }

    else if (option == "-q" || option == "quality") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      container->userSettings.quality.parse(argv[++i]);

      if (container->userSettings.quality.errored) {
        return invalidArgument("Invalid quality provided.");
      }

    }

    else if (option == "-s" || option == "--start") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      container->userSettings.startBeginning.parse(argv[++i]);

      if (container->userSettings.startBeginning.errored) {
        return invalidArgument("Invalid start time provided.");
      }
    }

    else if (option == "-t" || option == "--tune") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      Tunes::Tune tune = Tunes::getKey(argv[++i]);

      if (tune == Tunes::DEFAULT) {
        return invalidArgument("Invalid tune provided.");
      }

      container->userSettings.tune = tune;
    }

    else if (option == "-tr" || option == "--trim") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      container->userSettings.trim.parse(argv[++i]);

      if (container->userSettings.trim.errored) {
        return invalidArgument("Invalid trim times provided.");
      }
    }

    else {
      invalidArgument(argv[i]);
    }
  }
}

void UserArguments::invalidArgument(const char* arg) {
  Log::send({LogColor::fgRed(arg)});
}