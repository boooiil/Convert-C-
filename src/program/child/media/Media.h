/*********************************************************************
 * @file   Media.h
 * @brief  Media class header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef MEDIA
#define MEDIA

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

#include "../../generics/JSONSerializable.h"
#include "../../settings/enums/Activity.h"
#include "../../settings/enums/StringEnumDataHolder.h"
#include "../ffmpeg/probe/ProbeResult.h"
#include "MediaFile.h"
#include "MediaVideoProperties.h"
#include "MediaWorkingProperties.h"

/**
 * @brief Media class.
 *
 * Trrr
 *
 */
class Media : public JSONSerializable {
 public:
  /// @brief vector of arguments to be passed to ffmpeg
  std::vector<std::string> ffmpegArguments;
  long started;  /// @brief start time
  long ended;    /// @brief end time

  ProbeResult* probeResult;         /// @brief ProbeResult object
  MediaFile* file;                  /// @brief MediaFile object
  MediaVideoProperties* video;      /// @brief MediaVideoProperties object
  MediaWorkingProperties* working;  /// @brief MediaWorkingProperties object

  /**
   * @brief Create a Media object. (unused)
   *
   */
  Media();

  /**
   * @brief Create a Media object.
   *
   * @param[in] name - Name of the file.
   * @param[in] path - Path to the file (generally CWD).
   */
  Media(std::string name, std::string path);
  ~Media(void);

  /**
   * @brief Set the activity type.
   *
   * @param[in] activity - Activity type.
   */
  void setActivity(StringEnumDataHolder<Activity> activity);

  /**
   * @brief Do the statistics process.
   *
   * @param[out] container - Ptr to the Container object.
   */
  void doStatistics(void);

  /**
   * @brief Do the conversion process.
   *
   * @param[out] container - Ptr to the Container object.
   */
  void doConversion(void);

  /**
   * @brief Do the validation process.
   *
   * @param[out] container - Ptr to the Container object.
   */
  void doValidation(void);

  /**
   * @brief Build arguments required to process FFmpeg media with given
   * parameters.
   *
   * @param[in] isValidate  - TODO: I'm not sure what this does.
   */
  void buildFFmpegArguments(bool isValidate);

  /**
   * @brief Get the activity type.
   *
   * @return Activity::ActivityType - Activity type.
   */
  StringEnumDataHolder<Activity> getActivity(void);

  /**
   * @brief Check if the current media is processing.
   *
   * @return true if the media activity is STATISTICS, CONVERT or VALIDATE.
   * @return false if the media activity is WAITING-like, FINISHED, or
   * FAILED-like.
   */
  const bool isProcessing(void);

  /**
   * @brief Check if the current media has failed processing.
   *
   * @return true if the media activity is FAILED-like.
   */
  const bool hasFailed(void);

  /**
   * @brief Check if the current media has failed processing.
   *
   * @return true if the media activity is FINISHED.
   */
  const bool hasFinished(void);

  /**
   * @brief Check if the current media is waiting to be processed.
   *
   * @return true if the media activity is WAITING.
   */
  const bool isWaiting(void);

  /**
   * @brief Check if the current media is waiting for statistics.
   *
   * @return true if the media activity is WAITING_STATISTICS.
   */
  const bool isWaitingToStatistics(void);

  /**
   * @brief Check if the current media is waiting to convert.
   *
   * @return true if the media activity is WAITING_CONVERT.
   */
  const bool isWaitingToConvert(void);

  /**
   * @brief Check if the current media is waiting to validate.
   *
   * @return true if the media activity is WAITING_VALIDATE.
   */
  const bool isWaitingToValidate(void);

  void fromJSON(nlohmann::json) override;

  const nlohmann::json toJSON(void) const override;

 private:
  /// @brief activity type
  StringEnumDataHolder<Activity> activity;
};

#endif  // !MEDIA
