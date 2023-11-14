#if !defined(PROBE_RESULT_STREAM_AUDIO)
#define PROBE_RESULT_STREAM_AUDIO

#include "ProbeResultStream.h"

class ProbeResultStreamAudio : public ProbeResultStream {
 public:
  /** This constructor should never be called. */
  ProbeResultStreamAudio();

  /**
   * @brief Construct a new Probe Result Stream Audio object
   *
   * @param JSON The FFProbe stream JSON.
   */
  ProbeResultStreamAudio(nlohmann::json JSON);
  ~ProbeResultStreamAudio();

  std::string sample_fmt;
  std::string sample_rate;
  int channels;
  std::string channel_layout;
  int bits_per_sample;
  int initial_padding;
};

#endif  // PROBE_RESULT_STREAM_AUDIO
