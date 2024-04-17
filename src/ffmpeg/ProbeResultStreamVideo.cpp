#include "ProbeResultStreamVideo.h"

#include "../utils/RegexUtils.h"

/**
 * TODO: Validate ffmpeg verison to avoid missing fields
 */

ProbeResultStreamVideo::ProbeResultStreamVideo()
    : closed_captions(-1),
      film_grain(-1),
      has_b_frames(-1),
      height(-1),
      width(-1),
      coded_height(-1),
      coded_width(-1),
      is_avc(-1),
      level(-1),
      refs(-1) {}
ProbeResultStreamVideo::~ProbeResultStreamVideo() {}

ProbeResultStreamVideo::ProbeResultStreamVideo(nlohmann::json JSON) {
  Log::debug(
      {"[ProbeResultStreamVideo.cpp] Starting ProbeResultStreamVideo..."});
  ProbeResultStreamVideo::index = JSON["index"];

  if (!JSON["is_avc"].is_null()) {
    Log::debug({"[ProbeResultStreamVideo.cpp] is_avc: ", JSON["is_avc"]});
    ProbeResultStreamVideo::is_avc = RegexUtils::isMatch(
        JSON["is_avc"], "true", std::regex_constants::icase);
  }
  Log::debug({"[ProbeResultStreamVideo.cpp] codec_name: ", JSON["codec_name"]});
  ProbeResultStreamVideo::codec_name = JSON["codec_name"];
  Log::debug({"[ProbeResultStreamVideo.cpp] codec_long_name: ",
              JSON["codec_long_name"]});
  ProbeResultStreamVideo::codec_long_name = JSON["codec_long_name"];
  Log::debug({"[ProbeResultStreamVideo.cpp] codec_tag_string: ",
              JSON["codec_tag_string"]});
  ProbeResultStreamVideo::codec_tag_string = JSON["codec_tag_string"];
  Log::debug({"[ProbeResultStreamVideo.cpp] codec_tag: ", JSON["codec_tag"]});
  ProbeResultStreamVideo::codec_tag = JSON["codec_tag"];
  Log::debug({"[ProbeResultStreamVideo.cpp] codec_type: ", JSON["codec_type"]});
  ProbeResultStreamVideo::codec_type = JSON["codec_type"];
  Log::debug(
      {"[ProbeResultStreamVideo.cpp] r_frame_rate: ", JSON["r_frame_rate"]});
  ProbeResultStreamVideo::r_frame_rate = JSON["r_frame_rate"];
  Log::debug({"[ProbeResultStreamVideo.cpp] avg_frame_rate: ",
              JSON["avg_frame_rate"]});
  ProbeResultStreamVideo::avg_frame_rate = JSON["avg_frame_rate"];
  Log::debug({"[ProbeResultStreamVideo.cpp] time_base: ", JSON["time_base"]});
  ProbeResultStreamVideo::time_base = JSON["time_base"];
  Log::debug({"[ProbeResultStreamVideo.cpp] start_pts: ",
              std::to_string((int)JSON["start_pts"])});
  ProbeResultStreamVideo::start_pts = JSON["start_pts"];
  Log::debug({"[ProbeResultStreamVideo.cpp] start_time: ", JSON["start_time"]});
  ProbeResultStreamVideo::start_time = JSON["start_time"];
  /* Does not appear on linux (ubuntu), apt, ffmpeg=4.4.2-0ubuntu0.22.04.1 */
  // ProbeResultStreamVideo::extradata_size = JSON["extradata_size"];
  ProbeResultStreamVideo::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStreamVideo::tags = ProbeResultStreamTags(JSON["tags"]);
  Log::debug({"[ProbeResultStreamVideo.cpp] width: ",
              std::to_string((int)JSON["width"])});
  ProbeResultStreamVideo::width = JSON["width"];
  Log::debug({"[ProbeResultStreamVideo.cpp] height: ",
              std::to_string((int)JSON["height"])});
  ProbeResultStreamVideo::height = JSON["height"];
  Log::debug({"[ProbeResultStreamVideo.cpp] coded_width: ",
              std::to_string((int)JSON["coded_width"])});
  ProbeResultStreamVideo::coded_width = JSON["coded_width"];
  Log::debug({"[ProbeResultStreamVideo.cpp] coded_height: ",
              std::to_string((int)JSON["coded_height"])});
  ProbeResultStreamVideo::coded_height = JSON["coded_height"];
  Log::debug({"[ProbeResultStreamVideo.cpp] closed_captions: ",
              std::to_string((int)JSON["closed_captions"])});
  ProbeResultStreamVideo::closed_captions = JSON["closed_captions"];
  /* Does not appear on linux (ubuntu), apt, ffmpeg=4.4.2-0ubuntu0.22.04.1 */
  // ProbeResultStreamVideo::film_grain = JSON["film_grain"];
  Log::debug({"[ProbeResultStreamVideo.cpp] has_b_frames: ",
              std::to_string((int)JSON["has_b_frames"])});
  ProbeResultStreamVideo::has_b_frames = JSON["has_b_frames"];
  Log::debug({"[ProbeResultStreamVideo.cpp] sample_aspect_ratio: ",
              JSON["sample_aspect_ratio"]});
  ProbeResultStreamVideo::sample_aspect_ratio = JSON["sample_aspect_ratio"];
  Log::debug({"[ProbeResultStreamVideo.cpp] display_aspect_ratio: ",
              JSON["display_aspect_ratio"]});
  ProbeResultStreamVideo::display_aspect_ratio = JSON["display_aspect_ratio"];
  Log::debug({"[ProbeResultStreamVideo.cpp] pix_fmt: ", JSON["pix_fmt"]});
  ProbeResultStreamVideo::pix_fmt = JSON["pix_fmt"];
  Log::debug({"[ProbeResultStreamVideo.cpp] level: ",
              std::to_string((int)JSON["level"])});
  ProbeResultStreamVideo::level = JSON["level"];

  if (!JSON["color_range"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamVideo.cpp] color_range: ", JSON["color_range"]});
    ProbeResultStreamVideo::color_range = JSON["color_range"];
  }
  if (!JSON["color_space"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamVideo.cpp] color_space: ", JSON["color_space"]});
    ProbeResultStreamVideo::color_space = JSON["color_space"];
  }
  if (!JSON["color_transfer"].is_null()) {
    Log::debug({"[ProbeResultStreamVideo.cpp] color_transfer: ",
                JSON["color_transfer"]});
    ProbeResultStreamVideo::color_transfer = JSON["color_transfer"];
  }
  if (!JSON["color_primaries"].is_null()) {
    Log::debug({"[ProbeResultStreamVideo.cpp] color_primaries: ",
                JSON["color_primaries"]});
    ProbeResultStreamVideo::color_primaries = JSON["color_primaries"];
  }
  if (!JSON["chroma_location"].is_null()) {
    Log::debug({"[ProbeResultStreamVideo.cpp] chroma_location: ",
                JSON["chroma_location"]});
    ProbeResultStreamVideo::chroma_location = JSON["chroma_location"];
  }
  if (!JSON["field_order"].is_null()) {
    Log::debug(
        {"[ProbeResultStreamVideo.cpp] field_order: ", JSON["field_order"]});
    ProbeResultStreamVideo::field_order = JSON["field_order"];
  }
  if (!JSON["refs"].is_null()) {
    Log::debug({"[ProbeResultStreamVideo.cpp] refs: ",
                std::to_string((int)JSON["refs"])});
    ProbeResultStreamVideo::refs = JSON["refs"];
  }
  if (!JSON["nal_length_size"].is_null()) {
    Log::debug({"[ProbeResultStreamVideo.cpp] nal_length_size: ",
                JSON["nal_length_size"]});
    ProbeResultStreamVideo::nal_length_size = JSON["nal_length_size"];
  }
  if (!JSON["bits_per_raw_sample"].is_null()) {
    Log::debug({"[ProbeResultStreamVideo.cpp] bits_per_raw_sample: ",
                JSON["bits_per_raw_sample"]});
    ProbeResultStreamVideo::bits_per_raw_sample = JSON["bits_per_raw_sample"];
  }

  Log::debug({"[ProbeResultStreamVideo.cpp] Ended ProbeResultStreamVideo"});
}