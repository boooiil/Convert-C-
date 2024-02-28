#include "UserArguments.h"

#include "../logging/LogColor.h"
#include "../media/MediaDefinedFormat.h"
#include "../utils/ListUtils.h"
#include "../utils/RegexUtils.h"
#include "../utils/StringUtils.h"
#include "./Container.h"
#include "./Debug.h"
#include "./Ticker.h"

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
      std::string value = StringUtils::toLowerCase(argv[++i]);
      Log::debug({"[UserArguments.cpp] Value:", value});
      container->appEncodingDecision.audioStreams =
          ListUtils::splitv(value, ",");
    }

    else if (option == "-h" || option == "--help") {
      container->appEncodingDecision.printHelp = true;
    }

    else if (option == "-i" || option == "--info") {
      container->appEncodingDecision.printInformation = true;
    }

    else if (option == "-d" || option == "--debug") {
      Debug::toggle = true;
    }

    else if (option == "-e" || option == "--encoder") {
      // todo: create method to get encoder based on string input
    }

    else if (option == "-q" || option == "quality") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }
      std::string value = StringUtils::toLowerCase(argv[++i]);
      Log::debug({"[UserArguments.cpp] Value:", value});
      if (MediaDefinedFormat::formats.count(value) > 0) {
        container->appEncodingDecision.quality =
            MediaDefinedFormat::formats[value];
      } else if (RegexUtils::isMatch(value, "[0-9]+p")) {
        std::string quality_str = StringUtils::replaceAll(value, "p", "");
        int quality = std::stoi(quality_str);

        MediaDefinedFormat::addCustomFormat(quality);
        container->appEncodingDecision.quality =
            MediaDefinedFormat::formats[value];
      }

      else {
        return invalidArgument(container, "Incorrect quality provided.");
      }
    }

    else if (option == "-t" || option == "--tune") {
      // todo: iterate over the tune regex
      // that is all
    }

    else if (option == "-a" || option == "--amount") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }
      std::string value = StringUtils::toLowerCase(argv[++i]);
      Log::debug({"[UserArguments.cpp] Value:", value});
      container->appEncodingDecision.amount = std::stoi(value);
    }

    else if (option == "-c" || option == "--crop") {
      container->appEncodingDecision.crop = true;
    }

    else if (option == "-s" || option == "--start") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }
      std::string value = StringUtils::toLowerCase(argv[++i]);
      Log::debug({"[UserArguments.cpp] Value:", value});
      container->appEncodingDecision.startBeginning = value;
    }

    else if (option == "-tr" || option == "--trim") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }
      std::string value = StringUtils::toLowerCase(argv[++i]);
      Log::debug({"[UserArguments.cpp] Value:", value});
      container->appEncodingDecision.trim = value;
    }

    else if (option == "-b" || option == "--bitrate") {
      container->appEncodingDecision.useBitrate = true;
    }

    else if (option == "-co" || option == "--constrain") {
      container->appEncodingDecision.useConstrain = true;
    }

    else if (option == "-crf" || option == "--crf") {
      if (i + 1 >= argc) {
        return invalidArgument(container, "No value provided for argument.");
      }
      std::string value = StringUtils::toLowerCase(argv[++i]);
      Log::debug({"[UserArguments.cpp] Value:", value});
      container->appEncodingDecision.crfOverride = std::stoi(value);
    }

    else if (option == "-hwe" || option == "hardwareencode") {
      container->appEncodingDecision.useHardwareEncode = true;
    }

    else if (option == "-hwd" || option == "hardwaredecode") {
      container->appEncodingDecision.useHardwareDecode = true;
    }

    else if (option == "-o" || option == "--overwrite") {
      container->appEncodingDecision.overwrite = true;
    }

    else {
      invalidArgument(container, argv[i]);
    }
  }
}

void UserArguments::invalidArgument(Container* container, const char* arg) {
  Log::send({LogColor::fgRed(arg)});
}