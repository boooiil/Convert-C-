/*********************************************************************
 * @file   Decoders.h
 * @brief  Decoders class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#if !defined(DECODERS)
#define DECODERS

#include <string>
#include <unordered_map>

/**
 * @brief List of decoders supported by the application.
 *
 */
class Decoders {
 public:
  Decoders();
  ~Decoders();

  /**
   * @brief Enum of decoders supported by the application.
   *
   */
  enum Codec { AV1_CUVID, AV1_QSV, H264_CUVID, H264_QSV, HEVC_CUVID, HEVC_QSV };

  /**
   * @brief Get the string value of the enum.
   *
   * @param[in] codec - Desired codec.
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

#endif  // DECODERS
