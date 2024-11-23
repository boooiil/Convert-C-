#ifndef AUDIO_CODEC_FLAC_H
#define AUDIO_CODEC_FLAC_H

#include "../../../settings/enums/AudioCodec.h"
#include "../../../settings/enums/StringEnumDataHolder.h"
#include "BaseAudioCodec.h"

class AudioCodec_FLAC : public BaseAudioCodec {
 public:
  StringEnumDataHolder<AudioCodec> getType() override {
    return AudioCodec::FLAC;
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
        8,  // fl, fc, fr, rl, rr, lfe, sl, sr
        9,  // fl, fc, fr, rl, rr, lfe, sl, sr, rc
        10  // fl, fc, fr, rl, rr, lfe, sl, sr, rc, tl, tr
    };
  };
  int fallbackChannel() override { return 2; };

  std::vector<int> supportedSampleRates() override {
    return {8000,  11025, 12000, 16000, 22050,  24000,  32000, 44100,
            48000, 64000, 88200, 96000, 176400, 192000, 384000};
  };
  int fallbackSampleRate() override { return 96000; };

  std::vector<int> supportedBitDepths() override { return {8, 16, 24, 32}; };
  int fallbackBitDepth() override { return 24; };
};

#endif  // AUDIO_CODEC_FLAC_H