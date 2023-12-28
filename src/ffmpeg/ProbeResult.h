#if !defined(PROBE_RESULT)
#define PROBE_RESULT

#include "ProbeResultFormat.h"
#include "ProbeResultStream.h"
#include "ProbeResultStreamAudio.h"
#include "ProbeResultStreamSubtitle.h"
#include "ProbeResultStreamVideo.h"

/**
 * @brief This is the base JSON parse for the ffprobe result.
 *
 */
class ProbeResult {
 public:
  /** This constructor should never be called. */
  ProbeResult();

  /**
   * @brief Construct a new Probe Result object
   *
   * @param JSON The FFProbe result JSON.
   */
  ProbeResult(nlohmann::json JSON);
  ~ProbeResult();

  /**
   * @brief The parsed FFProbe format result.
   *
   */
  ProbeResultFormat format;

  /**
   * @brief The parsed FFProbe video streams result.
   *
   */
  std::vector<ProbeResultStreamVideo> videoStreams;

  /**
   * @brief The parsed FFProbe video streams result.
   *
   */
  std::vector<ProbeResultStreamAudio> audioStreams;

  /**
   * @brief The parsed FFProbe subtitle streams result.
   *
   */
  std::vector<ProbeResultStreamSubtitle> subtitleStreams;
};

#endif  // PROBE_RESULT
