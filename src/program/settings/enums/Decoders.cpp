#include "Decoders.h"

const StringEnumDataHolder<Decoders> Decoders::NONE("none", "None");

const StringEnumDataHolder<Decoders> Decoders::H264_CUVID("h264_cuvid",
                                                          "H264_CUVID");
const StringEnumDataHolder<Decoders> Decoders::HEVC_CUVID("hevc_cuvid",
                                                          "HEVC_CUVID");
const StringEnumDataHolder<Decoders> Decoders::AV1_CUVID("av1_cuvid",
                                                         "AV1_CUVID");

const StringEnumDataHolder<Decoders> Decoders::H264_QSV("h264_qsv", "H264_QSV");
const StringEnumDataHolder<Decoders> Decoders::HEVC_QSV("hevc_qsv", "HEVC_QSV");
const StringEnumDataHolder<Decoders> Decoders::AV1_QSV("av1_qsv", "AV1_QSV");
