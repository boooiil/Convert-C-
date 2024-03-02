/*********************************************************************
 * @file   Encoders.h
 * @brief  Enum of encoders and utility functions.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/
#if !defined(ENCODERS)
#define ENCODERS

#include <string>
#include <unordered_map>

/**
 * @brief Class for encoders.
 *
 */
class Encoders {
 public:
  Encoders();
  ~Encoders();

  /**
   * @brief Enum of encoders.
   *
   */
  enum Codec {
    AV1,
    AV1_AMF,
    AV1_NVENC,
    AV1_QSV,
    H264,
    H264_AMF,
    H264_NVENC,
    H264_QSV,
    HEVC,
    HEVC_AMF,
    HEVC_NVENC,
    HEVC_QSV,
    INVALID
  };

  /**
   * @brief Get the codec from a string.
   *
   * @param[in] codec - Desired codec.
   *
   * @return Codec enum.
   */
  static Codec getKey(std::string codec);

  /**
   * @brief Get the string value of the enum.
   *
   * @param[in] codec - Desired codec.
   *
   * @return String value of enum.
   */
  static std::string getValue(Codec codec);

  /**
   * @brief Check if the codec is H264.
   *
   * @param[in] codec - Desired codec.
   *
   * @return True if the codec is H264.
   */
  static bool isH264(Codec codec);

  /**
   * @brief Check if the codec is HEVC.
   *
   * @param[in] codec - Desired codec.
   *
   * @return True if the codec is HEVC.
   */
  static bool isHEVC(Codec codec);

  /**
   * @brief Check if the codec is AV1.
   *
   * @param[in] codec - Desired codec.
   *
   * @return True if the codec is AV1.
   */
  static bool isAV1(Codec codec);

  /**
   * @brief Check if the codec is a hardware encoder.
   *
   * @param[in] codec - Desired codec.
   *
   * @return True if the codec is a hardware encoder.
   */
  static bool isHardwareEncoder(Codec codec);

 private:
  /**
   * @brief Map of enum to string value.
   *
   */
  static std::unordered_map<Codec, std::string> codecMap;
};

#endif  // ENCODERS
