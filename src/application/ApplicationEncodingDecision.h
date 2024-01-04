/*********************************************************************
 * @file   ApplicationEncodingDecision.h
 * @brief  ApplicationEncodingDecision class definition.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef APPLICATION_ENCODING_DECISION
#define APPLICATION_ENCODING_DECISION

#include <string>
#include <vector>

/**
 * @brief Holds the user's encoding decision.
 */
class ApplicationEncodingDecision {
 public:
  ApplicationEncodingDecision(void);
  ~ApplicationEncodingDecision(void);

  /// @brief The number of audio streams wanted.
  std::vector<std::string> audioStreams;
  /// @brief The user's desired encoder
  std::string wantedEncoder;
  /// @brief The current encoder being used
  std::string runningEncoder;
  /// @brief The current decoder being used
  std::string runningDecoder;
  /// @brief Defined MediaFormat quality
  std::string quality;
  /// @brief Codec tune setting
  std::string tune;
  /// @brief Start the video from this time
  std::string startBeginning;
  /// @brief Trim the video to this time
  std::string trim;

  /// @brief Amount of concurrent conversions
  int amount;
  /// @brief CRF override
  int crfOverride;

  /// @brief Crop the video
  bool crop;
  /// @brief Use bitrate instead of CRF
  bool useBitrate;
  /// @brief Use strict bitrate values instead of variable
  bool useConstrain;
  /// @brief Validate the video after conversion
  bool validate;
  /// @brief Use hardware decode
  bool useHardwareDecode;
  /// @brief Use hardware encode
  bool useHardwareEncode;
  /// @brief Overwrite existing file
  bool overwrite;

  /**
   * @brief Validate the user's settings.
   *
   */
  void validateSettings(void);

 private:
};

#endif  //! APPLICATION_ENCODING_DECISION
