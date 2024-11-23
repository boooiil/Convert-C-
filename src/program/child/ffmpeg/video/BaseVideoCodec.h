#ifndef BASE_VIDEO_CODEC_H
#define BASE_VIDEO_CODEC_H

#include <set>
#include <vector>

#include "../../../../utils/logging/Logger.h"
#include "../../../settings/enums/Encoders.h"
#include "../../../settings/enums/MediaFormats.h"
#include "../../../settings/enums/ObjectEnumDataHolder.h"
#include "../../../settings/enums/StringEnumDataHolder.h"
#include "../../../settings/enums/Tunes.h"

class BaseVideoCodec {
 public:
  virtual ~BaseVideoCodec() {
    LOG_DEBUG("Deconstructing...");
    if (runningTune != nullptr) {
      LOG_DEBUG("Deleting Running Tune");
      delete runningTune;
    }
  }

  /**
   * @brief Get the type of video codec used by this encoder
   *
   * @return StringEnumDataHolder<Encoders>
   */
  virtual StringEnumDataHolder<Encoders> getType() {
    return Encoders::INVALID;
  };

  /**
   * @brief The control rate flag used by this codec.
   *
   * @return std::string
   */
  virtual std::string controlRateFlag() = 0;

  // what is a preset ?
  virtual std::vector<std::string> supportedPresets() = 0;
  virtual std::string fallbackPreset() = 0;

  const std::string getPreset(std::string preset) {
    return getParam(preset, &BaseVideoCodec::supportedPresets,
                    &BaseVideoCodec::fallbackPreset);
  }

  virtual std::vector<std::string> supportedLevels() = 0;
  virtual std::string fallbackLevel() = 0;

  const std::string getLevel(std::string level) {
    return getParam(level, &BaseVideoCodec::supportedLevels,
                    &BaseVideoCodec::fallbackLevel);
  }

  virtual std::vector<StringEnumDataHolder<Tunes>> supportedTunes() = 0;
  virtual StringEnumDataHolder<Tunes> fallbackTune() = 0;

  const StringEnumDataHolder<Tunes> getTune(StringEnumDataHolder<Tunes> tune) {
    return getParam(tune, &BaseVideoCodec::supportedTunes,
                    &BaseVideoCodec::fallbackTune);
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

  std::string runningPreset;
  std::string runningLevel;
  StringEnumDataHolder<Tunes>* runningTune;
};

#endif  // BASE_VIDEO_CODEC_H