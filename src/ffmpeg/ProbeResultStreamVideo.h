#if !defined(PROBE_RESULT_STREAM_VIDEO)
#define PROBE_RESULT_STREAM_VIDEO

#include "ProbeResultStream.h"

class ProbeResultStreamVideo : public ProbeResultStream {
 public:
  /** This constructor should never be called. */
  ProbeResultStreamVideo();

  /**
   * @brief Construct a new Probe Result Stream Video object
   *
   * @param JSON The FFProbe video stream JSON.
   */
  ProbeResultStreamVideo(nlohmann::json JSON);
  ~ProbeResultStreamVideo();

  std::string profile;
  int width;
  int height;
  int coded_width;
  int coded_height;
  int closed_captions;
  int film_grain;
  int has_b_frames;
  std::string sample_aspect_ratio;
  std::string display_aspect_ratio;
  std::string pix_fmt;
  int level;
  std::string color_range;
  std::string color_space;
  std::string color_transfer;
  std::string color_primaries;
  std::string chroma_location;
  std::string field_order;
  int refs;
  int is_avc;
  std::string nal_length_size;
  std::string bits_per_raw_sample;
};
#endif  // PROBE_RESULT_STREAM_VIDEO
