#include "AudioChannels.h"

#include <exception>

#include "../../../../logging/Log.h"
#include "../../../../utils/ListUtils.h"
#include "../VectorArgument.h"

AudioChannels::AudioChannels(void) : VectorArgument<int>() {
  helpMessage = "Number of audio channels. Example: 2,5.1,7.1";
};

AudioChannels::~AudioChannels(void){};

void AudioChannels::parse(std::string argument) {
  if (argument.empty()) {
    errored = true;
    return;
  }

  try {
    for (std::string channel : ListUtils::splitv(argument, ",")) {
      if (channel == "2") {
        value.push_back(2);
        continue;
      } else if (channel == "5.1" || channel == "6") {
        value.push_back(6);
        continue;
      } else if (channel == "7.1" || channel == "8") {
        value.push_back(8);
        continue;
      } else {
        Log::send(
            {"Audio channel count must be 2, 5.1 (6), or 7.1 (8): ", channel});
        errored = true;
      }
    }
  } catch (const std::exception& e) {
    Log::debug({"Failed to parse audio channels: ", argument, "\n", e.what()});
    errored = true;
    return;
  }
}
