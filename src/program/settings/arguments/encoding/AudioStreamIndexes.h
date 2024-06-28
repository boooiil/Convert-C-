#ifndef AUDIO_STREAM_INDEXES_H
#define AUDIO_STREAM_INDEXES_H

#include <string>
#include <vector>

#include "../VectorArgument.h"

class AudioStreamIndexes : public VectorArgument<int> {
 public:
  AudioStreamIndexes(void);
  ~AudioStreamIndexes(void);

  void parse(std::string argument) override;
};

#endif  // AUDIO_STREAM_INDEXES_H