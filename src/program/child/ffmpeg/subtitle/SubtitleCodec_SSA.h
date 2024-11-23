#ifndef SUBTITLE_CODEC_SSA_H
#define SUBTITLE_CODEC_SSA_H

#include "../../../settings/enums/StringEnumDataHolder.h"
#include "../../../settings/enums/SubtitleCodec.h"
#include "BaseSubtitleCodec.h"

class SubtitleCodec_SSA : public BaseSubtitleCodec {
 public:
  StringEnumDataHolder<SubtitleCodec> getType() { return SubtitleCodec::SSA; };
};

#endif  // SUBTITLE_CODEC_SSA_H