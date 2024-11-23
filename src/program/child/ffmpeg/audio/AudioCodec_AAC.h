#ifndef AUDIO_CODEC_AAC_H
#define AUDIO_CODEC_AAC_H

#include "../../../settings/enums/AudioCodec.h"
#include "../../../settings/enums/StringEnumDataHolder.h"
#include "BaseAudioCodec.h"

class AudioCodec_AAC : public BaseAudioCodec {
 public:
  StringEnumDataHolder<AudioCodec> getType() override {
    return AudioCodec::AAC;
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
    return {8000,  11025, 12000, 16000, 22050, 24000,
            32000, 44100, 48000, 64000, 88200, 96000};
  };
  int fallbackSampleRate() override { return 48000; };

  std::vector<int> supportedBitDepths() override { return {16, 24}; };
  int fallbackBitDepth() override { return 16; };
};

#endif  // AUDIO_CODEC_AAC_H