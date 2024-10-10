#include "Encoders.h"

#include "StringEnumDataHolder.h"

const StringEnumDataHolder<Encoders> Encoders::INVALID("invalid", "Invalid");

const StringEnumDataHolder<Encoders> Encoders::H264("h264", "H.264");
const StringEnumDataHolder<Encoders> Encoders::H264_AMF("h264_amf",
                                                        "H.264 AMF");
const StringEnumDataHolder<Encoders> Encoders::H264_NVENC("h264_nvenc",
                                                          "H.264 NVEnc");
const StringEnumDataHolder<Encoders> Encoders::H264_QSV("h264_qsv",
                                                        "H.264 QSV");

const StringEnumDataHolder<Encoders> Encoders::HEVC("hevc", "HEVC");
const StringEnumDataHolder<Encoders> Encoders::HEVC_AMF("hevc_amf", "HEVC AMF");
const StringEnumDataHolder<Encoders> Encoders::HEVC_NVENC("hevc_nvenc",
                                                          "HEVC NVEnc");
const StringEnumDataHolder<Encoders> Encoders::HEVC_QSV("hevc_qsv", "HEVC QSV");

const StringEnumDataHolder<Encoders> Encoders::AV1("av1", "AV1");
const StringEnumDataHolder<Encoders> Encoders::AV1_AMF("av1_amf", "AV1 AMF");
const StringEnumDataHolder<Encoders> Encoders::AV1_NVENC("av1_nvenc",
                                                         "AV1 NVEnc");
const StringEnumDataHolder<Encoders> Encoders::AV1_QSV("av1_qsv", "AV1 QSV");

bool Encoders::isH264(StringEnumDataHolder<Encoders> codec) {
  return codec == Encoders::H264 || codec == Encoders::H264_AMF ||
         codec == Encoders::H264_NVENC || codec == Encoders::H264_QSV;
}

bool Encoders::isHEVC(StringEnumDataHolder<Encoders> codec) {
  return codec == Encoders::HEVC || codec == Encoders::HEVC_AMF ||
         codec == Encoders::HEVC_NVENC || codec == Encoders::HEVC_QSV;
}

bool Encoders::isAV1(StringEnumDataHolder<Encoders> codec) {
  return codec == Encoders::AV1 || codec == Encoders::AV1_AMF ||
         codec == Encoders::AV1_NVENC || codec == Encoders::AV1_QSV;
}

bool Encoders::isHardwareEncoder(StringEnumDataHolder<Encoders> codec) {
  return codec == Encoders::AV1_AMF || codec == Encoders::AV1_NVENC ||
         codec == Encoders::AV1_QSV || codec == Encoders::H264_AMF ||
         codec == Encoders::H264_NVENC || codec == Encoders::H264_QSV ||
         codec == Encoders::HEVC_AMF || codec == Encoders::HEVC_NVENC ||
         codec == Encoders::HEVC_QSV;
}