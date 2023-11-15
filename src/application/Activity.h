#ifndef ACTIVITY
#define ACTIVITY

#include <string>
#include <unordered_map>

class Activity {
 public:
  Activity();
  ~Activity();

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
   * @param activityType Desired activity type.
   * @return std::string String value of enum.
   */
  static std::string getValue(ActivityType activityType);

 private:
  static std::unordered_map<ActivityType, std::string> activityMap;
};

#endif  // !ACTIVITY
