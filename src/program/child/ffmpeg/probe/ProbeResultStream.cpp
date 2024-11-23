#include "ProbeResultStream.h"

#include <nlohmann/json.hpp>
#include <string>

#include "../../../../utils/logging/Logger.h"
#include "ProbeResultStreamDisposition.h"
#include "ProbeResultStreamTags.h"

ProbeResultStream::ProbeResultStream()
    : index(-1), extradata_size(-1), start_pts(-1) {}
ProbeResultStream::~ProbeResultStream() = default;

ProbeResultStream::ProbeResultStream(nlohmann::json JSON) {
  if (!JSON["index"].is_null()) {
    LOG_DEBUG("index: ", std::to_string((int)JSON["index"]));
    ProbeResultStream::index = JSON["index"];
  }
  if (!JSON["codec_name"].is_null()) {
    LOG_DEBUG("codec_name: ", JSON["codec_name"]);
    ProbeResultStream::codec_name = JSON["codec_name"];
  }
  if (!JSON["codec_long_name"].is_null()) {
    LOG_DEBUG("codec_long_name: ", JSON["codec_long_name"]);
    ProbeResultStream::codec_long_name = JSON["codec_long_name"];
  }
  if (!JSON["codec_tag_string"].is_null()) {
    LOG_DEBUG("codec_tag_string: ", JSON["codec_tag_string"]);
    ProbeResultStream::codec_tag_string = JSON["codec_tag_string"];
  }
  if (!JSON["codec_tag"].is_null()) {
    LOG_DEBUG("codec_tag: ", JSON["codec_tag"]);
    ProbeResultStream::codec_tag = JSON["codec_tag"];
  }
  if (!JSON["codec_type"].is_null()) {
    LOG_DEBUG("codec_type: ", JSON["codec_type"]);
    ProbeResultStream::codec_type = JSON["codec_type"];
  }
  if (!JSON["r_frame_rate"].is_null()) {
    LOG_DEBUG("r_frame_rate: ", JSON["r_frame_rate"]);
    ProbeResultStream::r_frame_rate = JSON["r_frame_rate"];
  }
  if (!JSON["avg_frame_rate"].is_null()) {
    LOG_DEBUG("avg_frame_rate: ", JSON["avg_frame_rate"]);
    ProbeResultStream::avg_frame_rate = JSON["avg_frame_rate"];
  }
  if (!JSON["time_base"].is_null()) {
    LOG_DEBUG("time_base: ", JSON["time_base"]);
    ProbeResultStream::time_base = JSON["time_base"];
  }
  if (!JSON["start_pts"].is_null()) {
    LOG_DEBUG("start_pts: ", JSON["start_pts"]);
    ProbeResultStream::start_pts = JSON["start_pts"];
  }
  if (!JSON["start_time"].is_null()) {
    LOG_DEBUG("start_time: ", JSON["start_time"]);
    ProbeResultStream::start_time = JSON["start_time"];
  }
  if (!JSON["extradata_size"].is_null()) {
    LOG_DEBUG("extradata_size: ", JSON["extradata_size"]);
    ProbeResultStream::extradata_size = JSON["extradata_size"];
  }

  ProbeResultStream::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStream::tags = ProbeResultStreamTags(JSON["tags"]);
}