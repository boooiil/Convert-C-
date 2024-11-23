#ifndef AUDIO_CODEC_OPUS_H
#define AUDIO_CODEC_OPUS_H

#include "../../../settings/enums/AudioCodec.h"
#include "../../../settings/enums/StringEnumDataHolder.h"
#include "BaseAudioCodec.h"

class AudioCodec_OPUS : public BaseAudioCodec {
 public:
  StringEnumDataHolder<AudioCodec> getType() override {
    return AudioCodec::OPUS;
  };

  std::vector<int> supportedChannels() override {
    return {
        1,  // mono
        2,  // l, r
        3,  // fl, c, fr
        4,  // fl, fr, rl, rr
        5,  // fl, fc, fr, rl, rr
        6,  // fl, fc, fr, rl, rr, lfe
        7,  // fl, fc, fr, rl, rr, lfe, rc
        8   // fl, fc, fr, rl, rr, lfe, sl, sr
    };
  };
  int fallbackChannel() override { return 2; };

  std::vector<int> supportedSampleRates() override {
    return {8000, 12000, 16000, 24000, 48000};
  };
  int fallbackSampleRate() override { return 48000; };

  std::vector<int> supportedBitDepths() override { return {16}; };
  int fallbackBitDepth() override { return 16; };
};

#endif  // AUDIO_CODEC_OPUS_H