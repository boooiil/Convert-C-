#ifndef BASE_SUBTITLE_CODEC_H
#define BASE_SUBTITLE_CODEC_H

#include <vector>

#include "../../../settings/enums/StringEnumDataHolder.h"
#include "../../../settings/enums/SubtitleCodec.h"

class BaseSubtitleCodec {
 public:
  virtual StringEnumDataHolder<SubtitleCodec> getType() {
    return SubtitleCodec::NONE;
  };
};

#endif  // BASE_SUBTITLE_CODEC_H