#if !defined(PROBE_RESULT_STREAM)
#define PROBE_RESULT_STREAM

#include <string>

#include "ProbeResultStreamDisposition.h"
#include "ProbeResultStreamTags.h"

class ProbeResultStream {
 public:
  /** This constructor should never be called. */
  ProbeResultStream();

  /**
   * @brief Construct a new Probe Result Stream object
   *
   * @param JSON The FFProbe stream JSON.
   */
  ProbeResultStream(nlohmann::json JSON);
  ~ProbeResultStream();

  int index;
  std::string codec_name;
  std::string codec_long_name;
  std::string codec_tag_string;
  std::string codec_tag;
  std::string codec_type;
  std::string r_frame_rate;
  std::string avg_frame_rate;
  std::string time_base;
  int start_pts;
  std::string start_time;
  int extradata_size;

  /**
   * @brief The parsed FFProbe stream disposition result.
   *
   */
  ProbeResultStreamDisposition disposition;

  /**
   * @brief The parsed FFProbe stream tags result.
   *
   */
  ProbeResultStreamTags tags;
};

#endif  // PROBE_RESULT_STREAM
