#include "UserArguments.h"

#include "../logging/LogColor.h"
#include "../media/MediaDefinedFormat.h"
#include "../utils/RegexUtils.h"
#include "../utils/StringUtils.h"
#include "./Container.h"
#include "./Debug.h"

UserArguments::UserArguments() {}
UserArguments::~UserArguments() {}

void UserArguments::parse(Container& container, int argc, char* argv[]) {
  if (argc == 1) {
    // todo: send help message
    return UserArguments::invalidArgument(container, "No arguments provided.");
  }

  for (int i = 0; i < argc; i++) {
    container.log.sendPlain({"VA:LIE", argv[i]});
    std::string option = StringUtils::toLowerCase(argv[i]);
    std::string value = StringUtils::toLowerCase(argv[i + 1]);

    // yandere dev moment

    if (option == "-as" || option == "--audiostreams") {
      container.appEncodingDecision.audioStreams =
          StringUtils::split(value, ",");
    }

    else if (option == "-h" || option == "--help") {
      // todo: implement
    }

    else if (option == "-d" || option == "--debug") {
      Debug::toggle = true;
    }

    else if (option == "-e" || option == "--encoder") {
      // todo: create method to get encoder based on string input
    }

    else if (option == "-q" || option == "quality") {
      if (MediaDefinedFormat::formats.count(value) > 0) {
        container.appEncodingDecision.quality = value;
      } else if (RegexUtils::isMatch(value, "[0-9]+p")) {
        std::string quality_str = StringUtils::replaceAll(value, "p", "");
        int quality = std::stoi(quality_str);

        MediaDefinedFormat::addCustomFormat(quality);
        container.appEncodingDecision.quality = value;
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
      container.appEncodingDecision.amount = std::stoi(value);
    }

    else if (option == "-c" || option == "--crop") {
      container.appEncodingDecision.crop = true;
    }

    else if (option == "-s" || option == "--start") {
      container.appEncodingDecision.startBeginning = value;
    }

    else if (option == "-tr" || option == "--trim") {
      container.appEncodingDecision.trim = value;
    }

    else if (option == "-b" || option == "--bitrate") {
      container.appEncodingDecision.useBitrate = true;
    }

    else if (option == "-co" || option == "--constrain") {
      container.appEncodingDecision.useConstrain = true;
    }

    else if (option == "-crf" || option == "--crf") {
      container.appEncodingDecision.crfOverride = std::stoi(value);
    }

    else if (option == "-hwe" || option == "hardwareencode") {
      container.appEncodingDecision.useHardwareEncode = true;
    }

    else if (option == "-hwd" || option == "hardwaredecode") {
      container.appEncodingDecision.useHardwareDecode = true;
    }

    else if (option == "-o" || option == "--overwrite") {
      container.appEncodingDecision.overwrite = true;
    }

    else {
      invalidArgument(container, argv[i]);
    }
  }
}

void UserArguments::invalidArgument(Container& container, const char* arg) {
  container.log.send({LogColor::fgRed(arg)});
}