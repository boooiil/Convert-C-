#include "ProbeResultStream.h"

#include <string>

ProbeResultStream::ProbeResultStream()
    : index(-1), extradata_size(-1), start_pts(-1) {}
ProbeResultStream::~ProbeResultStream() {}

ProbeResultStream::ProbeResultStream(nlohmann::json JSON) {
  if (!JSON["index"].is_null()) {
    Log::debug({"[ProbeResultStream.cpp] index: ",
                std::to_string((int)JSON["index"])});
    ProbeResultStream::index = JSON["index"];
  }
  if (!JSON["codec_name"].is_null()) {
    Log::debug({"[ProbeResultStream.cpp] codec_name: ", JSON["codec_name"]});
    ProbeResultStream::codec_name = JSON["codec_name"];
  }
  if (!JSON["codec_long_name"].is_null()) {
    Log::debug(
        {"[ProbeResultStream.cpp] codec_long_name: ", JSON["codec_long_name"]});
    ProbeResultStream::codec_long_name = JSON["codec_long_name"];
  }
  if (!JSON["codec_tag_string"].is_null()) {
    Log::debug({"[ProbeResultStream.cpp] codec_tag_string: ",
                JSON["codec_tag_string"]});
    ProbeResultStream::codec_tag_string = JSON["codec_tag_string"];
  }
  if (!JSON["codec_tag"].is_null()) {
    Log::debug({"[ProbeResultStream.cpp] codec_tag: ", JSON["codec_tag"]});
    ProbeResultStream::codec_tag = JSON["codec_tag"];
  }
  if (!JSON["codec_type"].is_null()) {
    Log::debug({"[ProbeResultStream.cpp] codec_type: ", JSON["codec_type"]});
    ProbeResultStream::codec_type = JSON["codec_type"];
  }
  if (!JSON["r_frame_rate"].is_null()) {
    Log::debug(
        {"[ProbeResultStream.cpp] r_frame_rate: ", JSON["r_frame_rate"]});
    ProbeResultStream::r_frame_rate = JSON["r_frame_rate"];
  }
  if (!JSON["avg_frame_rate"].is_null()) {
    Log::debug(
        {"[ProbeResultStream.cpp] avg_frame_rate: ", JSON["avg_frame_rate"]});
    ProbeResultStream::avg_frame_rate = JSON["avg_frame_rate"];
  }
  if (!JSON["time_base"].is_null()) {
    Log::debug({"[ProbeResultStream.cpp] time_base: ", JSON["time_base"]});
    ProbeResultStream::time_base = JSON["time_base"];
  }
  if (!JSON["start_pts"].is_null()) {
    Log::debug({"[ProbeResultStream.cpp] start_pts: ", JSON["start_pts"]});
    ProbeResultStream::start_pts = JSON["start_pts"];
  }
  if (!JSON["start_time"].is_null()) {
    Log::debug({"[ProbeResultStream.cpp] start_time: ", JSON["start_time"]});
    ProbeResultStream::start_time = JSON["start_time"];
  }
  if (!JSON["extradata_size"].is_null()) {
    Log::debug(
        {"[ProbeResultStream.cpp] extradata_size: ", JSON["extradata_size"]});
    ProbeResultStream::extradata_size = JSON["extradata_size"];
  }

  ProbeResultStream::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStream::tags = ProbeResultStreamTags(JSON["tags"]);
}