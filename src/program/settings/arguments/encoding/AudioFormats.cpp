#include "AudioFormats.h"

#include <exception>
#include <string>
#include <vector>

#include "../../../../logging/Log.h"
#include "../../../../utils/ListUtils.h"
#include "../VectorArgument.h"

AudioFormats::AudioFormats(void) : VectorArgument<std::string>() {
  helpMessage = "Audio formats to be encoded. Example: aac,mp3";
};

AudioFormats::~AudioFormats(void){};

void AudioFormats::parse(std::string argument) {
  std::vector<std::string> formats = {
      "aac",  "ac3",  "ac4", "alac", "dca", "aptx", "dolby_e", "dts",
      "eac3", "flac", "mp1", "mp2",  "mp3", "opus", "truehd",  "vorbis"};

  if (argument.empty()) {
    errored = true;
    return;
  }

  try {
    for (std::string format : ListUtils::splitv(argument, ",")) {
      if (ListUtils::contains<std::string>(formats, format)) {
        value.push_back(format);
        continue;
      } else {
        Log::send({"Audio format must be one of the following: ",
                   ListUtils::join(formats, ", ")});
        errored = true;
      }
    }
  } catch (const std::exception& e) {
    Log::debug({"Failed to parse audio formats: ", argument, "\n", e.what()});
    errored = true;
    return;
  }
}
