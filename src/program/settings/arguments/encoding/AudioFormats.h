#ifndef AUDIO_FORMAT_H
#define AUDIO_FORMAT_H

#include <string>

#include "../VectorArgument.h"

class AudioFormats : public VectorArgument<std::string> {
 public:
  AudioFormats(void);
  ~AudioFormats(void);

  void parse(std::string argument) override;
};

#endif  // !AUDIO_FORMAT_H
