#ifndef SUBTITLE_CODEC_H
#define SUBTITLE_CODEC_H

#include <string>
#include <vector>

#include "StringEnumDataHolder.h"

class SubtitleCodec {
 public:
  static const StringEnumDataHolder<SubtitleCodec> NONE;      // default
  static const StringEnumDataHolder<SubtitleCodec> ASS;       // mkv default
  static const StringEnumDataHolder<SubtitleCodec> SRT;       // mkv
  static const StringEnumDataHolder<SubtitleCodec> SSA;       // mkv
  static const StringEnumDataHolder<SubtitleCodec> SUBRIP;    // ??
  static const StringEnumDataHolder<SubtitleCodec> DVB_SUB;   // ??
  static const StringEnumDataHolder<SubtitleCodec> WEBVTT;    // ??
  static const StringEnumDataHolder<SubtitleCodec> MOV_TEXT;  // mp4, mov

  static const std::vector<const StringEnumDataHolder<SubtitleCodec>*> _all() {
    return {
        &NONE, &ASS, &SRT, &SSA, &SUBRIP, &DVB_SUB, &WEBVTT, &MOV_TEXT,
    };
  };

  static const StringEnumDataHolder<SubtitleCodec> getKey(std::string value) {
    for (auto& item : _all()) {
      if (item->getName() == value) {
        return *item;
      }
    }
    return NONE;
  }
};

#endif  // SUBTITLE_CODEC_H