#include <string>
#if !defined(PROBE_RESULT_FORMAT)
#define PROBE_RESULT_FORMAT

#include "ProbeResultFormatTags.h"

class ProbeResultFormat {
 public:
  /** This constructor should never be called. */
  ProbeResultFormat();

  /**
   * @brief Construct a new Probe Result Format object
   *
   * @param JSON The FFProbe result JSON.
   */
  ProbeResultFormat(nlohmann::json JSON);
  ~ProbeResultFormat();

  std::string filename;
  int nb_streams;
  int nb_programs;
  std::string format_name;
  std::string format_long_name;
  std::string start_time;
  std::string duration;
  std::string size;
  std::string bit_rate;
  int probe_score;

  /**
   * @brief The parsed FFProbe format tags result.
   *
   */
  ProbeResultFormatTags tags;
};

#endif  // PROBE_RESULT_FORMAT
