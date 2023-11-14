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
    {Encoders::HEVC_QSV, "hevc_qsv"}};

Encoders::Encoders() {}
Encoders::~Encoders() {}

/**
 * @brief Get the value of the codec to be used in FFMpeg arguments.
 *
 * @param codec The encoder codec.
 * @return std::string The FFMpeg value of the codec.
 */
std::string Encoders::getValue(Encoders::Codec codec) {
  return codecMap.at(codec);
}