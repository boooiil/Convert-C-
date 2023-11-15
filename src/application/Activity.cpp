#include "Activity.h"

std::unordered_map<Activity::ActivityType, std::string> Activity::activityMap =
    {{ActivityType::CONVERT, "CONVERT"},
     {ActivityType::FAILED, "FAILED"},
     {ActivityType::FAILED_CODEC, "FAILED_CODEC"},
     {ActivityType::FAILED_CONTAINER, "FAILED_CONTAINER"},
     {ActivityType::FAILED_CORRUPT, "FAILED_CORRUPT"},
     {ActivityType::FAILED_FILE, "FAILED_FILE"},
     {ActivityType::FAILED_FILE_MISSING, "FAILED_FILE_MISSING"},
     {ActivityType::FAILED_FILE_PERMISSIONS, "FAILED_FILE_PERMISSIONS"},
     {ActivityType::FAILED_FILE_NOT_RECOGNIZED, "FAILED_FILE_NOT_RECOGNIZED"},
     {ActivityType::FAILED_HARDWARE, "FAILED_HARDWARE"},
     {ActivityType::FAILED_INVALID_AUDIO_STREAMS,
      "FAILED_INVALID_AUDIO_STREAMS"},
     {ActivityType::FAILED_SYSTEM, "FAILED_SYSTEM"},
     {ActivityType::FINISHED, "FINISHED"},
     {ActivityType::STATISTICS, "STATISTICS"},
     {ActivityType::WAITING, "WAITING"},
     {ActivityType::WAITING_CONVERT, "WAITING_CONVERT"},
     {ActivityType::WAITING_STATISTICS, "WAITING_STATISTICS"},
     {ActivityType::WAITING_VALIDATE, "WAITING_VALIDATE"},
     {ActivityType::VALIDATE, "VALIDATE"}};

Activity::Activity() {}
Activity::~Activity() {}

std::string Activity::getValue(Activity::ActivityType activityType) {
  return activityMap.at(activityType);
}