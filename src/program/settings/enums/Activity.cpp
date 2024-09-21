#include "Activity.h"

#include <string>
#include <unordered_map>

std::unordered_map<Activity::ActivityType, std::string> Activity::activityMap =
    {{ActivityType::CONVERT, "convert"},
     {ActivityType::FAILED, "failed"},
     {ActivityType::FAILED_CODEC, "failed_codec"},
     {ActivityType::FAILED_CONTAINER, "failed_container"},
     {ActivityType::FAILED_CORRUPT, "failed_corrupt"},
     {ActivityType::FAILED_FILE, "failed_file"},
     {ActivityType::FAILED_FILE_MISSING, "failed_file_missing"},
     {ActivityType::FAILED_FILE_PERMISSIONS, "failed_file_permissions"},
     {ActivityType::FAILED_FILE_NOT_RECOGNIZED, "failed_file_not_recognized"},
     {ActivityType::FAILED_HARDWARE, "failed_hardware"},
     {ActivityType::FAILED_INVALID_AUDIO_CHANNELS,
      "failed_invalid_audio_channels"},
     {ActivityType::FAILED_INVALID_AUDIO_STREAMS,
      "failed_invalid_audio_streams"},
     {ActivityType::FAILED_INVALID_DURATION_SS, "failed_invalid_duration_ss"},
     {ActivityType::FAILED_INVALID_DURATION_TO, "failed_invalid_duration_to"},
     {ActivityType::FAILED_INVALID_ENCODER, "failed_invalid_encoder"},
     {ActivityType::FAILED_JSON_PARSE, "failed_json_parse"},
     {ActivityType::FAILED_SYSTEM, "failed_system"},
     {ActivityType::FINISHED, "finished"},
     {ActivityType::STATISTICS, "statistics"},
     {ActivityType::WAITING, "waiting"},
     {ActivityType::WAITING_CONVERT, "waiting_convert"},
     {ActivityType::WAITING_STATISTICS, "waiting_statistics"},
     {ActivityType::WAITING_VALIDATE, "waiting_validate"},
     {ActivityType::VALIDATE, "validate"}};

Activity::Activity() {}
Activity::~Activity() {}

std::string Activity::getValue(Activity::ActivityType activityType) {
  return activityMap.at(activityType);
}

Activity::ActivityType Activity::getKey(std::string value) {
  for (auto const& [key, val] : activityMap) {
    if (val == value) {
      return key;
    }
  }
  return ActivityType::FAILED;
}
