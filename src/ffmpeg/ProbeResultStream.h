/*********************************************************************
 * @file   ProbeResultStream.h
 * @brief  Probe Result Stream class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#if !defined(PROBE_RESULT_STREAM)
#define PROBE_RESULT_STREAM

#include <string>

#include "../logging/Log.h"
#include "ProbeResultStreamDisposition.h"
#include "ProbeResultStreamTags.h"

/**
 * @brief This class became redundant when switched to individual stream list in
 * ProbeResult.h.
 *
 */
class ProbeResultStream {
 public:
  /** This constructor should never be called. */
  ProbeResultStream();

  /**
   * @brief Construct a new Probe Result Stream object
   *
   * @param[in] JSON - The FFProbe stream JSON.
   */
  ProbeResultStream(nlohmann::json JSON);
  ~ProbeResultStream();

  /// @brief stream index
  int index;

  /// @brief name of the codec
  std::string codec_name;
  /// @brief long name of the codec
  std::string codec_long_name;
  /// @brief ???
  std::string codec_tag_string;
  /// @brief ???
  std::string codec_tag;
  /// @brief video/audio/subtitle
  std::string codec_type;
  /// @brief stream frame rate
  std::string r_frame_rate;
  /// @brief stream average frame rate
  std::string avg_frame_rate;
  /// @brief stream time base
  std::string time_base;
  /// @brief ???
  int start_pts;
  /// @brief stream start time in seconds
  std::string start_time;
  /// @brief size of the extradata content in bytes
  int extradata_size;

  /// @brief The parsed FFProbe stream disposition result.
  ProbeResultStreamDisposition disposition;

  /// @brief The parsed FFProbe stream tags result.
  ProbeResultStreamTags tags;
};

#endif  // PROBE_RESULT_STREAM
