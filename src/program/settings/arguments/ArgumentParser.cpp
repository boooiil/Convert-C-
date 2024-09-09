#include "ArgumentParser.h"

#include <nlohmann/json.hpp>
#include <string>

#include "../../../logging/Log.h"
#include "../../../logging/LogColor.h"
#include "../../../utils/StringUtils.h"
#include "../../Program.h"
#include "../enums/Decoders.h"
#include "../enums/Encoders.h"
#include "../enums/GPUProviders.h"
#include "../enums/HWAccelerators.h"
#include "../enums/LoggingOptions.h"
#include "../enums/Platform.h"
#include "../enums/Tunes.h"

ArgumentParser::ArgumentParser()
    : GPU_Provider(GPUProviders::Provider::INTEL),
      platform(Platform::OPERATING_SYSTEM::_LINUX),
      tune(Tunes::Tune::FILM),
      validate(true) {}

ArgumentParser::~ArgumentParser(void) {}

void ArgumentParser::parse(int argc, char* argv[]) {
  if (argc < 2) {
    // return invalidArgument("No arguments provided");
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

    else if (option == "-ac" || option == "--audiochannels") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->audioChannels.parse(argv[++i]);

      if (this->audioChannels.errored) {
        return invalidArgument("Invalid audio channels.");
      }
    }

    else if (option == "-af" || option == "--audioformats") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }

      this->audioFormats.parse(argv[++i]);

      if (this->audioFormats.errored) {
        return invalidArgument("Invalid audio formats.");
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

    else if (option == "-dr" || option == "--display-refresh") {
      if (i + 1 >= argc) {
        return invalidArgument("No value provided for argument.");
      }
      this->displayRefresh.parse(argv[++i]);
      if (this->displayRefresh.errored) {
        return invalidArgument("Invalid display refresh value provided.");
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

    else if (option == "-hwd" || option == "hardwaredecode") {
      this->useHardwareDecode = true;
    }

    else if (option == "-hwe" || option == "hardwareencode") {
      this->useHardwareEncode = true;
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

    else if (option == "-parent") {
      this->isParent = true;
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

      Tunes::Tune tune_check = Tunes::getKey(argv[++i]);

      if (tune_check == Tunes::DEFAULT) {
        return invalidArgument("Invalid tune provided.");
      }

      this->tune = tune_check;
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
  Program::stopFlag = true;
}

nlohmann::json ArgumentParser::asJSON() {
  nlohmann::json argumentParser;

  argumentParser["platform"] = Platform::getValue(this->platform);
  argumentParser["gpu_provider"] = GPUProviders::getValue(this->GPU_Provider);

  argumentParser["supported_encoders"] = nlohmann::json::array();
  argumentParser["supported_decoders"] = nlohmann::json::array();
  argumentParser["supported_hw_accel"] = nlohmann::json::array();

  for (auto encoder : this->supportedEncoders) {
    argumentParser["supported_encoders"].push_back(Encoders::getValue(encoder));
  }

  for (auto decoder : this->supportedDecoders) {
    argumentParser["supported_decoders"].push_back(Decoders::getValue(decoder));
  }

  for (auto hw_accel : this->supportedHWAccel) {
    argumentParser["supported_hw_accel"].push_back(
        HWAccelerators::getValue(hw_accel));
  }

  argumentParser["audio_streams"] = this->audioStreams.get();
  argumentParser["display_refresh"] = this->displayRefresh.get();
  argumentParser["wanted_encoder"] = this->wantedEncoder.get();
  argumentParser["quality"] = this->quality.get().scale;
  argumentParser["tune"] = Tunes::getValue(this->tune);
  argumentParser["start_at"] = this->startBeginning.get();
  argumentParser["trim"] = this->trim.get();
  argumentParser["amount"] = this->amount.get();
  argumentParser["crf_override"] = this->crfOverride.get();
  argumentParser["crop"] = this->crop;
  argumentParser["use_bitrate"] = this->useBitrate;
  argumentParser["use_constrain"] = this->useConstrain;
  argumentParser["validate"] = this->validate;
  argumentParser["use_hardware_decode"] = this->useHardwareDecode;
  argumentParser["use_hardware_encode"] = this->useHardwareEncode;
  argumentParser["overwrite"] = this->overwrite;
  argumentParser["logging_format"] =
      LoggingOptions::getValue(this->loggingFormat);
  argumentParser["is_parent"] = this->isParent;
  argumentParser["print_information"] = this->printInformation;
  argumentParser["print_help"] = this->printHelp;

  return argumentParser;
}
