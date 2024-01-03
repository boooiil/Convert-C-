/*********************************************************************
 * @file   ProbeResultStreamSubtitle.h
 * @brief  Probe Result Stream Subtitle header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#if !defined(PROBE_RESULT_STREAM_SUBTITLE)
#define PROBE_RESULT_STREAM_SUBTITLE

#include "ProbeResultStream.h"

/**
 * @brief A class that represents a subtitle stream from FFProbe.
 */
class ProbeResultStreamSubtitle : public ProbeResultStream {
 public:
  /** This constructor should never be called. */
  ProbeResultStreamSubtitle();

  /**
   * @brief Construct a new Probe Result Stream Subtitle object
   *
   * @param[in] JSON - The FFProbe subtitle stream JSON.
   */
  ProbeResultStreamSubtitle(const nlohmann::json JSON);
  ~ProbeResultStreamSubtitle();

  /// @brief duration of the subtitle stream in ms
  int duration_ts;
  /// @brief duration of the subtitle stream in seconds
  std::string duration;
};

#endif  // PROBE_RESULT_STREAM_SUBTITLE
