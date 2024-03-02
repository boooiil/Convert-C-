#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include "../../ffmpeg/Tunes.h"
#include "../arguments/encoding/AudioStreamIndexes.h"
#include "../arguments/encoding/ConstantRateFactor.h"
#include "../arguments/encoding/ConstrainBitrate.h"
#include "../arguments/encoding/DesiredEncoder.h"
#include "../arguments/encoding/ParallelAmount.h"
#include "../arguments/encoding/UseBitrate.h"
#include "../arguments/encoding/UseHardwareDecode.h"
#include "../arguments/encoding/UseHardwareEncode.h"
#include "../arguments/misc/Debug.h"
#include "../arguments/misc/OverwriteExisting.h"
#include "../arguments/misc/PrintHelp.h"
#include "../arguments/misc/PrintInformation.h"
#include "../arguments/video/Crop.h"
#include "../arguments/video/Quality.h"
#include "../arguments/video/StartAt.h"
#include "../arguments/video/TrimBetween.h"

class UserSettings {
 public:
  UserSettings(void);
  ~UserSettings(void);
  /// @brief The number of audio streams wanted.
  AudioStreamIndexes audioStreams;
  /// @brief The user's desired encoder
  DesiredEncoder wantedEncoder;
  /// @brief The current encoder being used
  Quality quality;
  /// @brief Codec tune setting
  Tunes::Tune tune;
  /// @brief Start the video from this time
  StartAt startBeginning;
  /// @brief Trim the video to this time
  TrimBetween trim;

  /// @brief Amount of concurrent conversions
  ParallelAmount amount;
  /// @brief CRF override
  ConstantRateFactor crfOverride;

  /// @brief Crop the video
  Crop crop;
  /// @brief Use bitrate instead of CRF
  UseBitrate useBitrate;
  /// @brief Use strict bitrate values instead of variable
  ConstrainBitrate useConstrain;
  /// @brief Validate the video after conversion
  bool validate;
  /// @brief Use hardware decode
  UseHardwareDecode useHardwareDecode;
  /// @brief Use hardware encode
  UseHardwareEncode useHardwareEncode;
  /// @brief Overwrite existing file
  OverwriteExisting overwrite;

  /// @brief Print information about the video
  PrintInformation printInformation;

  /// @brief Print help information
  PrintHelp printHelp;

  /// @brief Debug mode
  Debug debug;

  /**
   * @brief Validate the user's settings.
   *
   */
  void validateSettings(void);
};

#endif  // USER_SETTINGS_H