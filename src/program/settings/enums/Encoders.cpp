#include "Encoders.h"

std::unordered_map<Encoders::Codec, std::string> Encoders::codecMap = {
    {Encoders::AV1, "av1"},
    {Encoders::AV1_AMF, "av1_amf"},
    {Encoders::AV1_NVENC, "av1_nvenc"},
    {Encoders::AV1_QSV, "av1_qsv"},
    {Encoders::H264, "h264"},
    {Encoders::H264_AMF, "h264_amf"},
    {Encoders::H264_NVENC, "h264_nvenc"},
    {Encoders::H264_QSV, "h264_qsv"},
    {Encoders::HEVC, "hevc"},
    {Encoders::HEVC_AMF, "hevc_amf"},
    {Encoders::HEVC_NVENC, "hevc_nvenc"},
    {Encoders::HEVC_QSV, "hevc_qsv"},
    {Encoders::INVALID, "invalid"}};

Encoders::Encoders() {}
Encoders::~Encoders() {}

Encoders::Codec Encoders::getKey(std::string codec) {
  for (auto const& [key, val] : codecMap) {
    if (val == codec) {
      return key;
    }
  }
  return Encoders::INVALID;
}

std::string Encoders::getValue(Encoders::Codec codec) {
  return codecMap.at(codec);
}

bool Encoders::isH264(Encoders::Codec codec) {
  return codec == Encoders::H264 || codec == Encoders::H264_AMF ||
         codec == Encoders::H264_NVENC || codec == Encoders::H264_QSV;
}

bool Encoders::isHEVC(Encoders::Codec codec) {
  return codec == Encoders::HEVC || codec == Encoders::HEVC_AMF ||
         codec == Encoders::HEVC_NVENC || codec == Encoders::HEVC_QSV;
}

bool Encoders::isAV1(Encoders::Codec codec) {
  return codec == Encoders::AV1 || codec == Encoders::AV1_AMF ||
         codec == Encoders::AV1_NVENC || codec == Encoders::AV1_QSV;
}

bool Encoders::isHardwareEncoder(Encoders::Codec codec) {
  return codec == Encoders::AV1_AMF || codec == Encoders::AV1_NVENC ||
         codec == Encoders::AV1_QSV || codec == Encoders::H264_AMF ||
         codec == Encoders::H264_NVENC || codec == Encoders::H264_QSV ||
         codec == Encoders::HEVC_AMF || codec == Encoders::HEVC_NVENC ||
         codec == Encoders::HEVC_QSV;
}