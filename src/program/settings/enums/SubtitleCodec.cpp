#include "SubtitleCodec.h"

#include "StringEnumDataHolder.h"

const StringEnumDataHolder<SubtitleCodec> SubtitleCodec::NONE("none", "None");
const StringEnumDataHolder<SubtitleCodec> SubtitleCodec::ASS("ass", "ASS");
const StringEnumDataHolder<SubtitleCodec> SubtitleCodec::SRT("srt", "SRT");
const StringEnumDataHolder<SubtitleCodec> SubtitleCodec::SSA("ssa", "SSA");
const StringEnumDataHolder<SubtitleCodec> SubtitleCodec::SUBRIP("subrip",
                                                                "SubRip");
const StringEnumDataHolder<SubtitleCodec> SubtitleCodec::DVB_SUB("dvb-sub",
                                                                 "DVB Sub");
const StringEnumDataHolder<SubtitleCodec> SubtitleCodec::WEBVTT("webvtt",
                                                                "WebVTT");
const StringEnumDataHolder<SubtitleCodec> SubtitleCodec::MOV_TEXT(
    "mov", "QuickTime (MOV)");