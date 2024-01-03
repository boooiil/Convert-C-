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
    HEVC_QSV
  };

  /**
   * @brief Get the string value of the enum.
   *
   * @param[in] codec - Desired codec.
   *
   * @return String value of enum.
   */
  static std::string getValue(Codec codec);

 private:
  /**
   * @brief Map of enum to string value.
   *
   */
  static std::unordered_map<Codec, std::string> codecMap;
};

#endif  // ENCODERS
