#if !defined(PROBE_RESULT_STREAM_TAGS)
#define PROBE_RESULT_STREAM_TAGS

#include <string>

#include "nlohmann/json.hpp"

class ProbeResultStreamTags {
 public:
  /** This constructor should never be called. */
  ProbeResultStreamTags();

  /**
   * @brief Construct a new Probe Result Stream Tags object
   *
   * @param JSON The FFProbe tag JSON.
   */
  ProbeResultStreamTags(nlohmann::json JSON);
  ~ProbeResultStreamTags();

  std::string title;
  std::string BPS;
  std::string NUMBER_OF_FRAMES;
  std::string NUMBER_OF_BYTES;
  std::string _STATISTICS_WRITING_APP;
  std::string _STATISTICS_WRITING_DATE_UTC;
  std::string _STATISTICS_TAGS;
  std::string ENCODER;
  std::string DURATION;
};

#endif  // PROBE_RESULT_STREAM_TAGS
