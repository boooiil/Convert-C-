#include "ProbeResultStreamSubtitle.h"

#include <nlohmann/json.hpp>

#include "../../../logging/Log.h"
#include "ProbeResultStreamDisposition.h"
#include "ProbeResultStreamTags.h"

/**
 * TODO: Validate ffmpeg verison to avoid missing fields
 */

ProbeResultStreamSubtitle::ProbeResultStreamSubtitle() : duration_ts(-1) {}
ProbeResultStreamSubtitle::~ProbeResultStreamSubtitle() {}

ProbeResultStreamSubtitle::ProbeResultStreamSubtitle(nlohmann::json JSON) {
  Log::debug(
      {"[ProbeResultStreamSubtitle.cpp] Starting "
       "ProbeResultStreamSubtitle..."});
  ProbeResultStreamSubtitle::index = JSON["index"];
  Log::debug(
      {"[ProbeResultStreamSubtitle.cpp] codec_name: ", JSON["codec_name"]});
  ProbeResultStreamSubtitle::codec_name = JSON["codec_name"];
  Log::debug({"[ProbeResultStreamSubtitle.cpp] codec_long_name: ",
              JSON["codec_long_name"]});
  ProbeResultStreamSubtitle::codec_long_name = JSON["codec_long_name"];
  Log::debug({"[ProbeResultStreamSubtitle.cpp] codec_tag_string: ",
              JSON["codec_tag_string"]});
  ProbeResultStreamSubtitle::codec_tag_string = JSON["codec_tag_string"];
  Log::debug(
      {"[ProbeResultStreamSubtitle.cpp] codec_tag: ", JSON["codec_tag"]});
  ProbeResultStreamSubtitle::codec_tag = JSON["codec_tag"];
  Log::debug(
      {"[ProbeResultStreamSubtitle.cpp] codec_type: ", JSON["codec_type"]});
  ProbeResultStreamSubtitle::codec_type = JSON["codec_type"];
  Log::debug(
      {"[ProbeResultStreamSubtitle.cpp] r_frame_rate: ", JSON["r_frame_rate"]});
  ProbeResultStreamSubtitle::r_frame_rate = JSON["r_frame_rate"];
  Log::debug({"[ProbeResultStreamSubtitle.cpp] avg_frame_rate: ",
              JSON["avg_frame_rate"]});
  ProbeResultStreamSubtitle::avg_frame_rate = JSON["avg_frame_rate"];
  Log::debug(
      {"[ProbeResultStreamSubtitle.cpp] time_base: ", JSON["time_base"]});
  ProbeResultStreamSubtitle::time_base = JSON["time_base"];
  Log::debug({"[ProbeResultStreamSubtitle.cpp] start_pts: ",
              std::to_string((int)JSON["start_pts"])});
  ProbeResultStreamSubtitle::start_pts = JSON["start_pts"];
  Log::debug(
      {"[ProbeResultStreamSubtitle.cpp] start_time: ", JSON["start_time"]});
  ProbeResultStreamSubtitle::start_time = JSON["start_time"];
  /* Does not appear on linux (ubuntu), apt, ffmpeg=4.4.2-0ubuntu0.22.04.1 */
  // ProbeResultStreamSubtitle::extradata_size = JSON["extradata_size"];
  ProbeResultStreamSubtitle::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStreamSubtitle::tags = ProbeResultStreamTags(JSON["tags"]);
  if (!JSON["duration_ts"].is_null()) {
    Log::debug({"[ProbeResultStreamSubtitle.cpp] duration_ts: ",
                std::to_string((int)JSON["duration_ts"])});
    ProbeResultStreamSubtitle::duration_ts = JSON["duration_ts"];
  }
  if (!JSON["duration"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamSubtitle.cpp] duration: ", JSON["duration"]});
    ProbeResultStreamSubtitle::duration = JSON["duration"];
  }
  Log::debug(
      {"[ProbeResultStreamSubtitle.cpp] Ended ProbeResultStreamSubtitle"});
}