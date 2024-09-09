#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

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
#include "../enums/Decoders.h"
#include "../enums/Encoders.h"
#include "../enums/GPUProviders.h"
#include "../enums/HWAccelerators.h"
#include "../enums/Platform.h"
#include "../enums/Tunes.h"
#include "encoding/AudioChannels.h"
#include "encoding/AudioFormats.h"
#include "misc/DisplayRefresh.h"

class ArgumentParser {
 public:
  ArgumentParser(void);
  ~ArgumentParser(void);

  /// @brief The number of audio streams wanted.
  AudioStreamIndexes audioStreams;
  /// @brief The audio formats wanted.
  AudioFormats audioFormats;
  /// @brief The audio channels wanted.
  AudioChannels audioChannels;
  /// @brief The current encoder being used
  Quality quality;
  /// @brief Codec tune setting
  Tunes::Tune tune;
  /// @brief Start the video from this time
  StartAt startBeginning;
  /// @brief Trim the video to this time
  TrimBetween trim;
  /// @brief The user's desired encoder
  DesiredEncoder wantedEncoder;

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

  /// @brief How often to refresh the display
  DisplayRefresh displayRefresh;

  /// @brief Print information about the video
  PrintInformation printInformation;

  /// @brief Print help information
  PrintHelp printHelp;

  void parse(int argc, char* argv[]);
  void invalidArgument(std::string);

  nlohmann::json asJSON(void);
};

#endif  // !ARGUMENT_PARSER_H
