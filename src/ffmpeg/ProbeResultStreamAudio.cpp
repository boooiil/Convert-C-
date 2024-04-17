#include "ProbeResultStreamAudio.h"

/**
 * TODO: Validate ffmpeg verison to avoid missing fields
 */

ProbeResultStreamAudio::ProbeResultStreamAudio()
    : channels(-1), bits_per_sample(-1), initial_padding(-1) {}
ProbeResultStreamAudio::~ProbeResultStreamAudio() {}

ProbeResultStreamAudio::ProbeResultStreamAudio(nlohmann::json JSON) {
  Log::debug(
      {"[ProbeResultStreamAudio.cpp] Starting ProbeResultStreamAudio..."});

  if (!JSON["index"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] index: ",
                std::to_string((int)JSON["index"])});
    ProbeResultStreamAudio::index = JSON["index"];
  }
  if (!JSON["codec_name"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamAudio.cpp] codec_name: ", JSON["codec_name"]});
    ProbeResultStreamAudio::codec_name = JSON["codec_name"];
  }
  if (!JSON["codec_long_name"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] codec_long_name: ",
                JSON["codec_long_name"]});
    ProbeResultStreamAudio::codec_long_name = JSON["codec_long_name"];
  }
  if (!JSON["codec_tag_string"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] codec_tag_string: ",
                JSON["codec_tag_string"]});
    ProbeResultStreamAudio::codec_tag_string = JSON["codec_tag_string"];
  }
  if (!JSON["codec_tag"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] codec_tag: ", JSON["codec_tag"]});
    ProbeResultStreamAudio::codec_tag = JSON["codec_tag"];
  }
  if (!JSON["codec_type"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamAudio.cpp] codec_type: ", JSON["codec_type"]});
    ProbeResultStreamAudio::codec_type = JSON["codec_type"];
  }
  if (!JSON["r_frame_rate"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamAudio.cpp] r_frame_rate: ", JSON["r_frame_rate"]});
    ProbeResultStreamAudio::r_frame_rate = JSON["r_frame_rate"];
  }
  if (!JSON["avg_frame_rate"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] avg_frame_rate: ",
                JSON["avg_frame_rate"]});
    ProbeResultStreamAudio::avg_frame_rate = JSON["avg_frame_rate"];
  }
  if (!JSON["time_base"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] time_base: ", JSON["time_base"]});
    ProbeResultStreamAudio::time_base = JSON["time_base"];
  }
  if (!JSON["start_pts"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] start_pts: ",
                std::to_string((int)JSON["start_pts"])});
    ProbeResultStreamAudio::start_pts = JSON["start_pts"];
  }
  if (!JSON["start_time"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamAudio.cpp] start_time: ", JSON["start_time"]});
    ProbeResultStreamAudio::start_time = JSON["start_time"];
  }
  if (!JSON["extradata_size"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] extradata_size: ",
                std::to_string((int)JSON["extradata_size"])});
    ProbeResultStreamAudio::extradata_size = JSON["extradata_size"];
  }

  ProbeResultStreamAudio::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);

  ProbeResultStreamAudio::tags = ProbeResultStreamTags(JSON["tags"]);

  if (!JSON["sample_fmt"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamAudio.cpp] sample_fmt: ", JSON["sample_fmt"]});
    ProbeResultStreamAudio::sample_fmt = JSON["sample_fmt"];
  }
  if (!JSON["sample_rate"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamAudio.cpp] sample_rate: ", JSON["sample_rate"]});
    ProbeResultStreamAudio::sample_rate = JSON["sample_rate"];
  }
  if (!JSON["channels"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] channels: ",
                std::to_string((int)JSON["channels"])});
    ProbeResultStreamAudio::channels = JSON["channels"];
  }
  if (!JSON["channel_layout"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] channel_layout: ",
                JSON["channel_layout"]});
    ProbeResultStreamAudio::channel_layout = JSON["channel_layout"];
  }
  if (!JSON["bits_per_sample"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] bits_per_sample: ",
                std::to_string((int)JSON["bits_per_sample"])});
    ProbeResultStreamAudio::bits_per_sample = JSON["bits_per_sample"];
  }
  if (!JSON["initial_padding"].is_null()) {
    Log::debug({"[ProbeResultStreamAudio.cpp] initial_padding: ",
                std::to_string((int)JSON["initial_padding"])});
    ProbeResultStreamAudio::initial_padding = JSON["initial_padding"];
  }
  Log::debug({"[ProbeResultStreamAudio.cpp] Ended ProbeResultStreamAudio"});
}