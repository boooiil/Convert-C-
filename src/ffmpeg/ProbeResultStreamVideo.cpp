#include "ProbeResultStreamVideo.h"

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
  ProbeResultStreamVideo::index = JSON["index"];
  ProbeResultStreamVideo::codec_name = JSON["codec_name"];
  ProbeResultStreamVideo::codec_long_name = JSON["codec_long_name"];
  ProbeResultStreamVideo::codec_tag_string = JSON["codec_tag_string"];
  ProbeResultStreamVideo::codec_tag = JSON["codec_tag"];
  ProbeResultStreamVideo::codec_type = JSON["codec_type"];
  ProbeResultStreamVideo::r_frame_rate = JSON["r_frame_rate"];
  ProbeResultStreamVideo::avg_frame_rate = JSON["avg_frame_rate"];
  ProbeResultStreamVideo::time_base = JSON["time_base"];
  ProbeResultStreamVideo::start_pts = JSON["start_pts"];
  ProbeResultStreamVideo::start_time = JSON["start_time"];
  ProbeResultStreamVideo::extradata_size = JSON["extradata_size"];
  ProbeResultStreamVideo::disposition =
      ProbeResultStreamDisposition(JSON["disposition"]);
  ProbeResultStreamVideo::tags = ProbeResultStreamTags(JSON["tags"]);
  ProbeResultStreamVideo::width = JSON["width"];
  ProbeResultStreamVideo::height = JSON["height"];
  ProbeResultStreamVideo::coded_width = JSON["coded_width"];
  ProbeResultStreamVideo::coded_height = JSON["coded_height"];
  ProbeResultStreamVideo::closed_captions = JSON["closed_captions"];
  ProbeResultStreamVideo::film_grain = JSON["film_grain"];
  ProbeResultStreamVideo::has_b_frames = JSON["has_b_frames"];
  ProbeResultStreamVideo::sample_aspect_ratio = JSON["sample_aspect_ratio"];
  ProbeResultStreamVideo::display_aspect_ratio = JSON["display_aspect_ratio"];
  ProbeResultStreamVideo::pix_fmt = JSON["pix_fmt"];
  ProbeResultStreamVideo::level = JSON["level"];
  ProbeResultStreamVideo::color_range = JSON["color_range"];
  ProbeResultStreamVideo::color_space = JSON["color_space"];
  ProbeResultStreamVideo::color_transfer = JSON["color_transfer"];
  ProbeResultStreamVideo::color_primaries = JSON["color_primaries"];
  ProbeResultStreamVideo::chroma_location = JSON["chroma_location"];
  ProbeResultStreamVideo::field_order = JSON["field_order"];
  ProbeResultStreamVideo::refs = JSON["refs"];
  ProbeResultStreamVideo::nal_length_size = JSON["nal_length_size"];
  ProbeResultStreamVideo::bits_per_raw_sample = JSON["bits_per_raw_sample"];
}