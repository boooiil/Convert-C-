#include "./AudioStreamIndexes.h"

#include "../../../logging/Log.h"
#include "../../../utils/ListUtils.h"

AudioStreamIndexes::AudioStreamIndexes(void) : VectorArgument<int>() {
  helpMessage = "Indexes of audio streams to be encoded. Example: 0,1,2";
};

AudioStreamIndexes::~AudioStreamIndexes(void){};

void AudioStreamIndexes::parse(std::string argument) {
  if (argument.empty()) {
    errored = true;
    return;
  }

  try {
    for (std::string index : ListUtils::splitv(argument, ",")) {

      int indexValue = std::stoi(index);

      if (indexValue < 0) {
        Log::send(
            {"Audio stream index must be greater than or equal to 0: ", index});
        errored = true;
        return;
      }

      value.push_back(indexValue);
    }
  } catch (const std::exception& e) {
    Log::debug(
        {"Failed to parse audio stream indexes: ", argument, "\n", e.what()});
    errored = true;
    return;
  }
}