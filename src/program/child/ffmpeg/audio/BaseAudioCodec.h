#ifndef BASE_AUDIO_CODEC_H
#define BASE_AUDIO_CODEC_H

#include <vector>

#include "../../../settings/enums/AudioCodec.h"
#include "../../../settings/enums/StringEnumDataHolder.h"

class BaseAudioCodec {
 public:
  virtual StringEnumDataHolder<AudioCodec> getType() {
    return AudioCodec::NONE;
  };

  virtual std::vector<int> supportedChannels() = 0;
  virtual int fallbackChannel() = 0;

  virtual const int getChannel(int channel) {
    return getParam(channel, &BaseAudioCodec::supportedChannels,
                    &BaseAudioCodec::fallbackChannel);
  }

  virtual std::vector<int> supportedSampleRates() = 0;
  virtual int fallbackSampleRate() = 0;

  virtual const int getSampleRate(int sampleRate) {
    return getParam(sampleRate, &BaseAudioCodec::supportedSampleRates,
                    &BaseAudioCodec::fallbackSampleRate);
  }

  virtual std::vector<int> supportedBitDepths() = 0;
  virtual int fallbackBitDepth() = 0;

  virtual const int getBitDepth(int bitDepth) {
    return getParam(bitDepth, &BaseAudioCodec::supportedBitDepths,
                    &BaseAudioCodec::fallbackBitDepth);
  }

 private:
  template <typename T, typename C>
  const T getParam(T search, std::vector<T> (C::*provider)(),
                   T (C::*fallback)()) {
    auto params = (this->*provider)();

    for (auto& p : params) {
      if (p == search) {
        return p;
      }
    }
    return (this->*fallback)();
  }

  int runningChannel = 2;
  int runningSampleRate = 41000;
  int runningBitDepth = 16;
};

#endif  // BASE_AUDIO_CODEC_H