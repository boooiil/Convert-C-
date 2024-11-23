#ifndef SUBTITLE_CODEC_ASS_H
#define SUBTITLE_CODEC_ASS_H

#include "../../../settings/enums/StringEnumDataHolder.h"
#include "../../../settings/enums/SubtitleCodec.h"
#include "BaseSubtitleCodec.h"

class SubtitleCodec_ASS : public BaseSubtitleCodec {
 public:
  StringEnumDataHolder<SubtitleCodec> getType() { return SubtitleCodec::ASS; };
};

#endif  // SUBTITLE_CODEC_ASS_H