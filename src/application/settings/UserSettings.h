#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include "../../ffmpeg/Decoders.h"
#include "../../ffmpeg/Encoders.h"
#include "../../ffmpeg/HWAccelerators.h"
#include "../../ffmpeg/Tunes.h"
#include "../GPUProviders.h"
#include "../Platform.h"
#include "../arguments/encoding/AudioStreamIndexes.h"
#include "../arguments/encoding/ConstantRateFactor.h"
#include "../arguments/encoding/ConstrainBitrate.h"
#include "../arguments/encoding/DesiredEncoder.h"
#include "../arguments/encoding/ParallelAmount.h"
#include "../arguments/encoding/UseBitrate.h"
#include "../arguments/encoding/UseHardwareDecode.h"
#include "../arguments/encoding/UseHardwareEncode.h"
#include "../arguments/misc/IsParent.h"
#include "../arguments/misc/LoggingFormat.h"
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

  /// @brief The current operating system of the user's machine
  Platform::OPERATING_SYSTEM platform;
  /// @brief The current GPU of the user's machine
  GPUProviders::Provider GPU_Provider;
  /// @brief The supported encoders
  std::vector<Encoders::Codec> supportedEncoders;
  /// @brief The supported decoders
  std::vector<Decoders::Codec> supportedDecoders;
  /// @brief The supported hardware accelerators
  std::vector<HWAccelerators::Accelerator> supportedHWAccel;
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
  /// @brief Format for display output.
  LoggingFormat loggingFormat;
  /// @brief Run as child process.
  IsParent isParent;

  /// @brief Print information about the video
  PrintInformation printInformation;

  /// @brief Print help information
  PrintHelp printHelp;

  /**
   * @brief Validate the user's settings.
   *
   */
  void validateSettings(void);

  /**
   * @brief Finds the hardware details of the user's machine
   * @return void
   */
  void findHardwareDetails(void);
};

#endif  // USER_SETTINGS_H