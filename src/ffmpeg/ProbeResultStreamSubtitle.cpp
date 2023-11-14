#include "ProbeResultStreamSubtitle.h"

ProbeResultStreamSubtitle::ProbeResultStreamSubtitle() : duration_ts(-1) {}
ProbeResultStreamSubtitle::~ProbeResultStreamSubtitle() {}

ProbeResultStreamSubtitle::ProbeResultStreamSubtitle(nlohmann::json JSON) {
  ProbeResultStreamSubtitle::index = JSON["index"];
  ProbeResultStreamSubtitle::codec_name = JSON["codec_name"];
  ProbeResultStreamSubtitle::codec_long_name = JSON["codec_long_name"];
  ProbeResultStreamSubtitle::codec_tag_string = JSON["codec_tag_string"];
  ProbeResultStreamSubtitle::codec_tag = JSON["codec_tag"];
  ProbeResultStreamSubtitle::codec_type = JSON["codec_type"];
  ProbeResultStreamSubtitle::r_frame_rate = JSON["r_frame_rate"];
  ProbeResultStreamSubtitle::avg_frame_rate = JSON["avg_frame_rate"];
  ProbeResultStreamSubtitle::time_base = JSON["time_base"];
  ProbeResultStreamSubtitle::start_pts = JSON["start_pts"];
  ProbeResultStreamSubtitle::start_time = JSON["start_time"];
  ProbeResultStreamSubtitle::extradata_size = JSON["extradata_size"];
  ProbeResultStreamSubtitle::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStreamSubtitle::tags = ProbeResultStreamTags(JSON["tags"]);
  ProbeResultStreamSubtitle::duration_ts = JSON["duration_ts"];
  ProbeResultStreamSubtitle::duration = JSON["duration"];
}