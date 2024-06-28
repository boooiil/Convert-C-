#ifndef TUNES_H
#define TUNES_H

#include <string>
#include <unordered_map>

class Tunes {
 public:
  Tunes();
  ~Tunes();

  /**
   * @brief Enum of tunes.
   *
   */
  enum Tune {
    FILM,
    ANIMATION,
    GRAIN,
    STILL_IMAGE,
    PSNR,
    SSIM,
    FAST_DECODE,
    ZERO_LATENCY,
    TEXTURE_COMPRESSION,
    PROXY,
    HIGH_QUALITY,
    LOW_LATENCY,
    ZERO_LATENCY_LOW_LATENCY,
    LOSSLESS,
    DEFAULT
  };

  /**
   * @brief Get the enum value of the string.
   *
   * @param[in] value - Desired tune.
   *
   * @return Enum value of string.
   */
  static Tune getKey(std::string value);

  /**
   * @brief Get the string value of the enum.
   *
   * @param[in] tune - Desired tune.
   *
   * @return String value of enum.
   */
  static std::string getValue(Tune tune);

  static std::unordered_map<Tunes::Tune, std::string> tuneMap;
};

#endif  // TUNES_H