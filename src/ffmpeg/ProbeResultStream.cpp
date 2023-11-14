#include "ProbeResultStream.h"

ProbeResultStream::ProbeResultStream()
    : index(-1), extradata_size(-1), start_pts(-1) {}
ProbeResultStream::~ProbeResultStream() {}

ProbeResultStream::ProbeResultStream(nlohmann::json JSON) {
  ProbeResultStream::index = JSON["index"];
  ProbeResultStream::codec_name = JSON["codec_name"];
  ProbeResultStream::codec_long_name = JSON["codec_long_name"];
  ProbeResultStream::codec_tag_string = JSON["codec_tag_string"];
  ProbeResultStream::codec_tag = JSON["codec_tag"];
  ProbeResultStream::codec_type = JSON["codec_type"];
  ProbeResultStream::r_frame_rate = JSON["r_frame_rate"];
  ProbeResultStream::avg_frame_rate = JSON["avg_frame_rate"];
  ProbeResultStream::time_base = JSON["time_base"];
  ProbeResultStream::start_pts = JSON["start_pts"];
  ProbeResultStream::start_time = JSON["start_time"];
  ProbeResultStream::extradata_size = JSON["extradata_size"];
  ProbeResultStream::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStream::tags = ProbeResultStreamTags(JSON["tags"]);
}