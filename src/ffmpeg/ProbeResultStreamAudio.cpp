#include "ProbeResultStreamAudio.h"

/**
 * TODO: Validate ffmpeg verison to avoid missing fields
 */

ProbeResultStreamAudio::ProbeResultStreamAudio()
    : channels(-1), bits_per_sample(-1), initial_padding(-1) {}
ProbeResultStreamAudio::~ProbeResultStreamAudio() {}

ProbeResultStreamAudio::ProbeResultStreamAudio(nlohmann::json JSON) {
  ProbeResultStreamAudio::index = JSON["index"];
  Log::debug({"[ProbeResultStreamAudio.cpp] codec_name: ", JSON["codec_name"]});
  ProbeResultStreamAudio::codec_name = JSON["codec_name"];
  Log::debug({"[ProbeResultStreamAudio.cpp] codec_long_name: ",
              JSON["codec_long_name"]});
  ProbeResultStreamAudio::codec_long_name = JSON["codec_long_name"];
  Log::debug({"[ProbeResultStreamAudio.cpp] codec_tag_string: ",
              JSON["codec_tag_string"]});
  ProbeResultStreamAudio::codec_tag_string = JSON["codec_tag_string"];
  Log::debug({"[ProbeResultStreamAudio.cpp] codec_tag: ", JSON["codec_tag"]});
  ProbeResultStreamAudio::codec_tag = JSON["codec_tag"];
  Log::debug({"[ProbeResultStreamAudio.cpp] codec_type: ", JSON["codec_type"]});
  ProbeResultStreamAudio::codec_type = JSON["codec_type"];
  Log::debug(
      {"[ProbeResultStreamAudio.cpp] r_frame_rate: ", JSON["r_frame_rate"]});
  ProbeResultStreamAudio::r_frame_rate = JSON["r_frame_rate"];
  Log::debug({"[ProbeResultStreamAudio.cpp] avg_frame_rate: ",
              JSON["avg_frame_rate"]});
  ProbeResultStreamAudio::avg_frame_rate = JSON["avg_frame_rate"];
  Log::debug({"[ProbeResultStreamAudio.cpp] time_base: ", JSON["time_base"]});
  ProbeResultStreamAudio::time_base = JSON["time_base"];
  Log::debug({"[ProbeResultStreamAudio.cpp] start_pts: ",
              std::to_string((int)JSON["start_pts"])});
  ProbeResultStreamAudio::start_pts = JSON["start_pts"];
  Log::debug({"[ProbeResultStreamAudio.cpp] start_time: ", JSON["start_time"]});
  ProbeResultStreamAudio::start_time = JSON["start_time"];
  /* Does not appear on linux (ubuntu), apt, ffmpeg=4.4.2-0ubuntu0.22.04.1 */
  // ProbeResultStreamAudio::extradata_size = JSON["extradata_size"];
  ProbeResultStreamAudio::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStreamAudio::tags = ProbeResultStreamTags(JSON["tags"]);
  Log::debug({"[ProbeResultStreamAudio.cpp] sample_fmt: ", JSON["sample_fmt"]});
  ProbeResultStreamAudio::sample_fmt = JSON["sample_fmt"];
  Log::debug(
      {"[ProbeResultStreamAudio.cpp] sample_rate: ", JSON["sample_rate"]});
  ProbeResultStreamAudio::sample_rate = JSON["sample_rate"];
  Log::debug({"[ProbeResultStreamAudio.cpp] channels: ",
              std::to_string((int)JSON["channels"])});
  ProbeResultStreamAudio::channels = JSON["channels"];
  Log::debug({"[ProbeResultStreamAudio.cpp] channel_layout: ",
              JSON["channel_layout"]});
  ProbeResultStreamAudio::channel_layout = JSON["channel_layout"];
  Log::debug({"[ProbeResultStreamAudio.cpp] bits_per_sample: ",
              std::to_string((int)JSON["bits_per_sample"])});
  ProbeResultStreamAudio::bits_per_sample = JSON["bits_per_sample"];
  /* Does not appear on linux (ubuntu), apt, ffmpeg=4.4.2-0ubuntu0.22.04.1 */
  // ProbeResultStreamAudio::initial_padding = JSON["initial_padding"];
}