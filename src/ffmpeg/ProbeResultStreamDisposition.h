#if !defined(PROBE_RESULT_STREAM_DISPOSITION)
#define PROBE_RESULT_STREAM_DISPOSITION

#include "nlohmann/json.hpp"

class ProbeResultStreamDisposition {
 public:
  /** This constructor should never be called. */
  ProbeResultStreamDisposition();

  /**
   * @brief Construct a new Probe Result Stream Disposition object
   *
   * @param JSON The FFProbe stream disposition JSON.
   */
  ProbeResultStreamDisposition(nlohmann::json JSON);
  ~ProbeResultStreamDisposition();

  int default_;
  int dub;
  int original;
  int comment;
  int lyrics;
  int karaoke;
  int forced;
  int hearing_impaired;
  int visual_impaired;
  int clean_effects;
  int attached_pic;
  int timed_thumbnails;
  int captions;
  int descriptions;
  int metadata;
  int dependent;
  int still_image;
};

#endif  // PROBE_RESULT_STREAM_DISPOSITION
