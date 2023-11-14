#if !defined(PROBE_RESULT_STREAM_SUBTITLE)
#define PROBE_RESULT_STREAM_SUBTITLE

#include "ProbeResultStream.h"

class ProbeResultStreamSubtitle : public ProbeResultStream {
 public:
  /** This constructor should never be called. */
  ProbeResultStreamSubtitle();

  /**
   * @brief Construct a new Probe Result Stream Subtitle object
   *
   * @param JSON The FFProbe subtitle stream JSON.
   */
  ProbeResultStreamSubtitle(nlohmann::json JSON);
  ~ProbeResultStreamSubtitle();

  int duration_ts;
  std::string duration;
};

#endif  // PROBE_RESULT_STREAM_SUBTITLE
