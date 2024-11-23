#ifndef AUDIO_CODEC_MP3_H
#define AUDIO_CODEC_MP3_H

#include "../../../settings/enums/AudioCodec.h"
#include "../../../settings/enums/StringEnumDataHolder.h"
#include "BaseAudioCodec.h"

class AudioCodec_MP3 : public BaseAudioCodec {
 public:
  StringEnumDataHolder<AudioCodec> getType() override {
    return AudioCodec::MP3;
  };

  std::vector<int> supportedChannels() override {
    return {
        1,  // mono
        2   // l, r
    };
  };
  int fallbackChannel() override { return 2; };

  std::vector<int> supportedSampleRates() override {
    return {8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000};
  };
  int fallbackSampleRate() override { return 48000; };

  std::vector<int> supportedBitDepths() override { return {16}; };
  int fallbackBitDepth() override { return 16; };
};

#endif  // AUDIO_CODEC_MP3_H