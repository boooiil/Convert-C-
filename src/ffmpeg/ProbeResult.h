#if !defined(PROBE_RESULT)
#define PROBE_RESULT

#include "ProbeResultFormat.h"
#include "ProbeResultStream.h"

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
   * @brief The parsed FFProbe streams result.
   *
   */
  std::vector<ProbeResultStream> streams;
};

#endif  // PROBE_RESULT
