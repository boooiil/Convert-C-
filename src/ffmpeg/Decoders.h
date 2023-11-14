#if !defined(DECODERS)
#define DECODERS

#include <string>
#include <unordered_map>

class Decoders {
 public:
  Decoders();
  ~Decoders();

  enum Codec { AV1_CUVID, AV1_QSV, H264_CUVID, H264_QSV, HEVC_CUVID, HEVC_QSV };

  /**
   * @brief Get the string value of the enum.
   *
   * @param codec Desired codec.
   * @return std::string String value of enum.
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
