#if !defined(PROBE_RESULT_FORMAT_TAGS)
#define PROBE_RESULT_FORMAT_TAGS

#include <string>

#include "nlohmann/json.hpp"

class ProbeResultFormatTags {
 public:
  /** This constructor should never be called. */
  ProbeResultFormatTags();

  /**
   * @brief Construct a new Probe Result Format Tags object
   *
   * @param JSON The FFProbe tag JSON.
   */
  ProbeResultFormatTags(nlohmann::json JSON);
  ~ProbeResultFormatTags();

  std::string ENCODER;
};

#endif  // PROBE_RESULT_FORMAT_TAGS
