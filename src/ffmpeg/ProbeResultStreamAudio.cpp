#include "ProbeResultStreamAudio.h"

/**
 * TODO: Validate ffmpeg verison to avoid missing fields
 */

ProbeResultStreamAudio::ProbeResultStreamAudio()
    : channels(-1), bits_per_sample(-1), initial_padding(-1) {}
ProbeResultStreamAudio::~ProbeResultStreamAudio() {}

ProbeResultStreamAudio::ProbeResultStreamAudio(nlohmann::json JSON) {
  ProbeResultStreamAudio::index = JSON["index"];
  ProbeResultStreamAudio::codec_name = JSON["codec_name"];
  ProbeResultStreamAudio::codec_long_name = JSON["codec_long_name"];
  ProbeResultStreamAudio::codec_tag_string = JSON["codec_tag_string"];
  ProbeResultStreamAudio::codec_tag = JSON["codec_tag"];
  ProbeResultStreamAudio::codec_type = JSON["codec_type"];
  ProbeResultStreamAudio::r_frame_rate = JSON["r_frame_rate"];
  ProbeResultStreamAudio::avg_frame_rate = JSON["avg_frame_rate"];
  ProbeResultStreamAudio::time_base = JSON["time_base"];
  ProbeResultStreamAudio::start_pts = JSON["start_pts"];
  ProbeResultStreamAudio::start_time = JSON["start_time"];
  /* Does not appear on linux (ubuntu), apt, ffmpeg=4.4.2-0ubuntu0.22.04.1 */
  // ProbeResultStreamAudio::extradata_size = JSON["extradata_size"];
  ProbeResultStreamAudio::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStreamAudio::tags = ProbeResultStreamTags(JSON["tags"]);
  ProbeResultStreamAudio::sample_fmt = JSON["sample_fmt"];
  ProbeResultStreamAudio::sample_rate = JSON["sample_rate"];
  ProbeResultStreamAudio::channels = JSON["channels"];
  ProbeResultStreamAudio::channel_layout = JSON["channel_layout"];
  ProbeResultStreamAudio::bits_per_sample = JSON["bits_per_sample"];
  /* Does not appear on linux (ubuntu), apt, ffmpeg=4.4.2-0ubuntu0.22.04.1 */
  // ProbeResultStreamAudio::initial_padding = JSON["initial_padding"];
}