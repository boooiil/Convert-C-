#include "ArgumentParser.h"

#include <string>

#include "../../../logging/Log.h"
#include "../../../logging/LogColor.h"
#include "../../../utils/StringUtils.h"
#include "../enums/Tunes.h"

ArgumentParser::ArgumentParser() {}

ArgumentParser::~ArgumentParser(void) {}

void ArgumentParser::parse(int argc, char* argv[]) {
  if (argc < 2) {
    return invalidArgument("No arguments provided");
  }

  // Skip the first argument, which is the program name
  for (int i = 1; i < argc; i++) {
    Log::debug({"[UserArguments.cpp] Option:", argv[i]});
    std::string option = StringUtils::toLowerCase(argv[i]);

    // yandere dev moment
    if (option == "-a" || option == "--amount") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->amount.parse(argv[++i]);

      if (this->amount.errored) {
        return invalidArgument("Invalid amount provided.");
      }
    }

    else if (option == "-as" || option == "--audiostreams") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->audioStreams.parse(argv[++i]);

      if (this->audioStreams.errored) {
        return invalidArgument("Invalid audio stream indexes.");
      }
    }

    else if (option == "-b" || option == "--bitrate") {
      this->useBitrate = true;
    }

    else if (option == "-c" || option == "--crop") {
      this->crop = true;
    }

    else if (option == "-parent") {
      this->isParent = true;
    }

    else if (option == "-co" || option == "--constrain") {
      this->useConstrain = true;
    }

    else if (option == "-crf" || option == "--crf") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->crfOverride.parse(argv[++i]);

      if (this->crfOverride.errored) {
        return invalidArgument("Invalid crf value provided.");
      }
    }

    else if (option == "-e" || option == "--encoder") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->wantedEncoder.parse(argv[++i]);

      if (this->wantedEncoder.errored) {
        return invalidArgument("Invalid encoder provided.");
      }

    }

    else if (option == "-h" || option == "--help") {
      this->printHelp = true;
    }

    else if (option == "-hwe" || option == "hardwareencode") {
      this->useHardwareEncode = true;
    }

    else if (option == "-hwd" || option == "hardwaredecode") {
      this->useHardwareDecode = true;
    }

    else if (option == "-i" || option == "--info") {
      this->printInformation = true;
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

      this->loggingFormat.parse(argv[++i]);

      if (this->loggingFormat.errored) {
        return invalidArgument("Invalid logging format provided.");
      }

    }

    else if (option == "-o" || option == "--overwrite") {
      this->overwrite = true;
    }

    else if (option == "-q" || option == "quality") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->quality.parse(argv[++i]);

      if (this->quality.errored) {
        return invalidArgument("Invalid quality provided.");
      }

    }

    else if (option == "-s" || option == "--start") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->startBeginning.parse(argv[++i]);

      if (this->startBeginning.errored) {
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

      this->tune = tune;
    }

    else if (option == "-tr" || option == "--trim") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->trim.parse(argv[++i]);

      if (this->trim.errored) {
        return invalidArgument("Invalid trim times provided.");
      }
    }

    else {
      invalidArgument(argv[i]);
    }
  }
}

void ArgumentParser::invalidArgument(std::string message) {
  Log::send({LogColor::fgRed(message)});
}
