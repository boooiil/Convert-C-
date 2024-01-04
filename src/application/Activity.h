/*********************************************************************
 * @file   Activity.h
 * @brief  Activity class header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef ACTIVITY
#define ACTIVITY

#include <string>
#include <unordered_map>

/**
 * @brief Enum for activity types and utility functions.
 */
class Activity {
 public:
  Activity();
  ~Activity();

  /// @brief Enum for activity types.
  enum ActivityType {
    CONVERT,
    FAILED,
    FAILED_CODEC,
    FAILED_CONTAINER,
    FAILED_CORRUPT,
    FAILED_FILE,
    FAILED_FILE_MISSING,
    FAILED_FILE_PERMISSIONS,
    FAILED_FILE_NOT_RECOGNIZED,
    FAILED_HARDWARE,
    FAILED_INVALID_AUDIO_STREAMS,
    FAILED_SYSTEM,
    FINISHED,
    STATISTICS,
    WAITING,
    WAITING_CONVERT,
    WAITING_STATISTICS,
    WAITING_VALIDATE,
    VALIDATE
  };

  /**
   * @brief Get the string value of the enum.
   *
   * @param[in] activityType - Desired activity type.
   * @return String value of enum.
   */
  static std::string getValue(ActivityType activityType);

 private:
  /// @brief Map of activity types to string values.
  static std::unordered_map<ActivityType, std::string> activityMap;
};

#endif  // !ACTIVITY
