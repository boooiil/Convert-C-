#include "ArgumentParser.h"

#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

#include "../../../logging/Log.h"
#include "../../../logging/LogColor.h"
#include "../../../utils/StringUtils.h"
#include "../../Program.h"
#include "../enums/Encoders.h"
#include "../enums/LoggingOptions.h"
#include "../enums/Tunes.h"
#include "./ArgumentRegistry.h"
#include "FlagArgument.h"
#include "GenericArgument.h"
#include "IntegerArgument.h"
#include "StringArgument.h"
#include "TimeStringArgument.h"
#include "TimeStringVectorArgument.h"
#include "VectorArgument.h"

ArgumentParser::ArgumentParser() : tune(Tunes::Tune::FILM) {}

ArgumentParser::~ArgumentParser(void) {}

void ArgumentParser::prepare() {
  ArgumentRegistry::addFn add = ArgumentRegistry::add;

  std::shared_ptr<IntegerArgument> ia = std::make_shared<IntegerArgument>(
      "-a", "--amount", "Amount of media to process", 1);

  add("-a", ia);
  add("--amount", ia);

  std::shared_ptr<VectorArgument<int>> iva = std::make_shared<
      VectorArgument<int>>(
      "-ac", "--audiochannels",
      "Specify number of audio channels for each audio stream. (Will default "
      "to original channel count if not specified)",
      std::vector<int>());

  add("-ac", iva);
  add("--audiochannels", iva);

  std::shared_ptr<VectorArgument<std::string>> sva =
      std::make_shared<VectorArgument<std::string>>(
          "-aco", "--audiocodec",
          "Specify audio formats for each audio stream. (Will default to "
          "original "
          "format if not specified)",
          std::vector<std::string>());

  add("-aco", sva);
  add("--audiocodec", sva);

  iva = std::make_shared<VectorArgument<int>>(
      "-as", "--audiostreams",
      "Specify audio streams to include in the "
      "output. (Will default to all "
      "streams if not specified)",
      std::vector<int>());

  add("-as", iva);
  add("--audiostreams", iva);

  std::shared_ptr<FlagArgument> fa =
      std::make_shared<FlagArgument>("-b", "--bitrate",
                                     "Use a bitrate instead of a quality "
                                     "setting. (Will default to quality "
                                     "if not specified)",
                                     false);

  add("-b", fa);
  add("--bitrate", fa);

  fa = std::make_shared<FlagArgument>(
      "-c", "--crop", "Crop the video to the specified ratio.", false);

  add("-c", fa);
  add("--crop", fa);

  fa = std::make_shared<FlagArgument>(
      "-co", "--constrain", "Constrain the bitrate to the specified value.",
      false);

  add("-co", fa);
  add("--constrain", fa);

  ia = std::make_shared<IntegerArgument>(
      "-crf", "--crf", "Set the CRF value for the output.", -1);

  add("-crf", ia);
  add("--crf", ia);

  ia = std::make_shared<IntegerArgument>(
      "-dr", "--displayrefresh",
      "Set the display refresh rate for the output. (Will default to the "
      "original refresh rate if not specified)",
      1000);

  add("-dr", ia);
  add("--displayrefresh", ia);

  // TODO: encoder (Encoders)

  fa = std::make_shared<FlagArgument>("-h", "--help", "Print the help message.",
                                      false);

  add("-h", fa);
  add("--help", fa);

  fa = std::make_shared<FlagArgument>(
      "-hwd", "--hardwaredecode", "Use hardware decoding if available.", true);

  add("-hwd", fa);
  add("--hardwaredecode", fa);

  fa = std::make_shared<FlagArgument>(
      "-hwe", "--hardwareencode", "Use hardware encoding if available.", false);

  add("-hwe", fa);
  add("--hardwareencode", fa);

  fa = std::make_shared<FlagArgument>(
      "-i", "--info", "Print information about the input file.", false);

  add("-i", fa);
  add("--info", fa);

  // TODO: logging format (LoggingOptions)

  fa = std::make_shared<FlagArgument>(
      "-o", "--overwrite", "Overwrite the output file if it exists.", false);

  add("-o", fa);
  add("--overwrite", fa);

  fa = std::make_shared<FlagArgument>("-parent", "-parent",
                                      "Run as a parent process.", false);

  add("-parent", fa);

  // TODO: quality (MediaFormat)

  std::shared_ptr<TimeStringArgument> sa = std::make_shared<TimeStringArgument>(
      "-ss", "--start", "Start the video at the specified time.",
      std::string());

  add("-ss", sa);
  add("--start", sa);

  // TODO: tune (Tunes)

  std::shared_ptr<TimeStringVectorArgument> tsva =
      std::make_shared<TimeStringVectorArgument>(
          "-tr", "--trim", "Trim the video to the specified time.",
          std::vector<std::string>());

  add("-tr", tsva);
  add("--trim", tsva);
}

void ArgumentParser::parse(int argc, char* argv[]) {
  if (argc < 2) {
    // return invalidArgument("No arguments provided");
  }

  // Skip the first argument, which is the program name
  for (int i = 1; i < argc; i++) {
    Log::send({"[UserArguments.cpp] Option:", argv[i]});
    std::string option = StringUtils::toLowerCase(argv[i]);

    /**
     * ***********************************
     *
     * OLD CHECK FOR ENUM ARGUMENTS
     *
     * ***********************************
     */

    if (option == "-e" || option == "--encoder") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->wantedEncoder.parse(argv[++i]);

      if (this->wantedEncoder.isErrored()) {
        return invalidArgument("Invalid encoder provided.");
      }
      continue;
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

      if (this->loggingFormat.isErrored()) {
        return invalidArgument("Invalid logging format provided.");
      }
      continue;
    }

    else if (option == "-q" || option == "quality") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->quality.parse(argv[++i]);

      if (this->quality.isErrored()) {
        return invalidArgument("Invalid quality provided.");
      }
      continue;
    }

    else if (option == "-t" || option == "--tune") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      Tunes::Tune tune_check = Tunes::getKey(argv[++i]);

      if (tune_check == Tunes::DEFAULT) {
        return invalidArgument("Invalid tune provided.");
      }

      this->tune = tune_check;
      continue;
    }

    /**
     * ***********************************
     *
     * NEW CHECK FOR REGISTERED ARGUMENTS
     *
     * ***********************************
     */

    std::shared_ptr<GenericArgument> argument = ArgumentRegistry::get(option);

    if (argument == nullptr) {
      invalidArgument(argv[i]);
      continue;
    }

    std::shared_ptr<FlagArgument> flagArgument =
        std::dynamic_pointer_cast<FlagArgument>(argument);

    if (flagArgument != nullptr) {
      flagArgument->parse("true");
      continue;
    } else {
      argument->parse(argv[++i]);

      if (argument->isErrored()) {
        invalidArgument(std::string(argv[i - 1]) +
                        " was provided invalid parameter " +
                        std::string(argv[i]));
        Log::send({argument->getHelpMessage()});
        continue;
      }
    }
  }
}

void ArgumentParser::invalidArgument(std::string message) {
  Log::send({LogColor::fgRed(message)});
  Program::stopFlag = true;
}

nlohmann::json ArgumentParser::asJSON() {
  // TODO: implement visitor pattern for this

  nlohmann::json argumentParser;

  for (auto& [flag, argument] : ArgumentRegistry::get_all()) {
    Log::send({flag, argument->getLongFlag(),
               flag == argument->getLongFlag() ? "True" : "False"});
    if (flag != argument->getLongFlag())
      argumentParser[flag] = argument->toString();
  }

  argumentParser["wanted_encoder"] =
      Encoders::getValue(this->wantedEncoder.get());
  argumentParser["quality"] = this->quality.get().scale;
  argumentParser["tune"] = Tunes::getValue(this->tune);
  argumentParser["logging_format"] =
      LoggingOptions::getValue(this->loggingFormat);

  return argumentParser;
}
