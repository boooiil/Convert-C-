#ifndef AUDIO_CHANNELS_H
#define AUDIO_CHANNELS_H

#include <string>

#include "../VectorArgument.h"

class AudioChannels : public VectorArgument<int> {
 public:
  AudioChannels(void);
  ~AudioChannels(void);

  void parse(std::string argument);
};

#endif  // !AUDIO_CHANNELS_H
