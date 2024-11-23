#include "ProbeResultStreamSubtitle.h"

#include <nlohmann/json.hpp>

#include "../../../../utils/logging/Logger.h"
#include "ProbeResultStreamDisposition.h"
#include "ProbeResultStreamTags.h"

/**
 * TODO: Validate ffmpeg verison to avoid missing fields
 */

ProbeResultStreamSubtitle::ProbeResultStreamSubtitle() : duration_ts(-1) {}
ProbeResultStreamSubtitle::~ProbeResultStreamSubtitle() {}

ProbeResultStreamSubtitle::ProbeResultStreamSubtitle(nlohmann::json JSON) {
  LOG_DEBUG(
      "Starting "
      "ProbeResultStreamSubtitle...");
  ProbeResultStreamSubtitle::index = JSON["index"];
  LOG_DEBUG("codec_name: ", JSON["codec_name"]);
  ProbeResultStreamSubtitle::codec_name = JSON["codec_name"];
  LOG_DEBUG("codec_long_name: ", JSON["codec_long_name"]);
  ProbeResultStreamSubtitle::codec_long_name = JSON["codec_long_name"];
  LOG_DEBUG("codec_tag_string: ", JSON["codec_tag_string"]);
  ProbeResultStreamSubtitle::codec_tag_string = JSON["codec_tag_string"];
  LOG_DEBUG("codec_tag: ", JSON["codec_tag"]);
  ProbeResultStreamSubtitle::codec_tag = JSON["codec_tag"];
  LOG_DEBUG("codec_type: ", JSON["codec_type"]);
  ProbeResultStreamSubtitle::codec_type = JSON["codec_type"];
  LOG_DEBUG("r_frame_rate: ", JSON["r_frame_rate"]);
  ProbeResultStreamSubtitle::r_frame_rate = JSON["r_frame_rate"];
  LOG_DEBUG("avg_frame_rate: ", JSON["avg_frame_rate"]);
  ProbeResultStreamSubtitle::avg_frame_rate = JSON["avg_frame_rate"];
  LOG_DEBUG("time_base: ", JSON["time_base"]);
  ProbeResultStreamSubtitle::time_base = JSON["time_base"];
  LOG_DEBUG("start_pts: ", std::to_string((int)JSON["start_pts"]));
  ProbeResultStreamSubtitle::start_pts = JSON["start_pts"];
  LOG_DEBUG("start_time: ", JSON["start_time"]);
  ProbeResultStreamSubtitle::start_time = JSON["start_time"];
  /* Does not appear on linux (ubuntu), apt, ffmpeg=4.4.2-0ubuntu0.22.04.1
   */
  // ProbeResultStreamSubtitle::extradata_size = JSON["extradata_size"];
  ProbeResultStreamSubtitle::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStreamSubtitle::tags = ProbeResultStreamTags(JSON["tags"]);
  if (!JSON["duration_ts"].is_null()) {
    LOG_DEBUG("duration_ts: ", std::to_string((int)JSON["duration_ts"]));
    ProbeResultStreamSubtitle::duration_ts = JSON["duration_ts"];
  }
  if (!JSON["duration"].is_null()) {
    LOG_DEBUG("duration: ", JSON["duration"]);
    ProbeResultStreamSubtitle::duration = JSON["duration"];
  }
  LOG_DEBUG("Ended ProbeResultStreamSubtitle");
}