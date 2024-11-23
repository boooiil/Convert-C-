#ifndef AUDIO_CODEC_EAC3_H
#define AUDIO_CODEC_EAC3_H

#include "../../../settings/enums/AudioCodec.h"
#include "../../../settings/enums/StringEnumDataHolder.h"
#include "BaseAudioCodec.h"

class AudioCodec_EAC3 : public BaseAudioCodec {
 public:
  StringEnumDataHolder<AudioCodec> getType() override {
    return AudioCodec::EAC3;
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
    return {
        32000,  // 32 kHz
        44100,  // 44.1 kHz
        48000,  // 48 kHz
        64000,  // 64 kHz
        96000,  // 96 kHz
        128000  // 128 kHz
    };
  };
  int fallbackSampleRate() override { return 48000; };

  std::vector<int> supportedBitDepths() override { return {16, 24}; };
  int fallbackBitDepth() override { return 16; };
};

#endif  // AUDIO_CODEC_EAC3_H