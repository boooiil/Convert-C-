/*********************************************************************
 * @file   Activity.h
 * @brief  Activity class header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <vector>

#include "StringEnumDataHolder.h"

/**
 * @brief Enum for activity types and utility functions.
 */
class Activity {
 public:
  static const StringEnumDataHolder<Activity> CONVERT;
  static const StringEnumDataHolder<Activity> FAILED;
  static const StringEnumDataHolder<Activity> FAILED_CODEC;
  static const StringEnumDataHolder<Activity> FAILED_CONTAINER;
  static const StringEnumDataHolder<Activity> FAILED_CORRUPT;
  static const StringEnumDataHolder<Activity> FAILED_FILE;
  static const StringEnumDataHolder<Activity> FAILED_FILE_MISSING;
  static const StringEnumDataHolder<Activity> FAILED_FILE_PERMISSIONS;
  static const StringEnumDataHolder<Activity> FAILED_FILE_NOT_RECOGNIZED;
  static const StringEnumDataHolder<Activity> FAILED_HARDWARE;
  static const StringEnumDataHolder<Activity> FAILED_INVALID_AUDIO_CHANNELS;
  static const StringEnumDataHolder<Activity> FAILED_INVALID_AUDIO_STREAMS;
  static const StringEnumDataHolder<Activity> FAILED_INVALID_DURATION_SS;
  static const StringEnumDataHolder<Activity> FAILED_INVALID_DURATION_TO;
  static const StringEnumDataHolder<Activity> FAILED_INVALID_ENCODER;
  static const StringEnumDataHolder<Activity> FAILED_JSON_PARSE;
  static const StringEnumDataHolder<Activity> FAILED_SYSTEM;
  static const StringEnumDataHolder<Activity> FINISHED;
  static const StringEnumDataHolder<Activity> STATISTICS;
  static const StringEnumDataHolder<Activity> WAITING;
  static const StringEnumDataHolder<Activity> WAITING_CONVERT;
  static const StringEnumDataHolder<Activity> WAITING_STATISTICS;
  static const StringEnumDataHolder<Activity> WAITING_VALIDATE;
  static const StringEnumDataHolder<Activity> VALIDATE;

  static const std::vector<const StringEnumDataHolder<Activity>*> _all() {
    return {&CONVERT,
            &FAILED,
            &FAILED_CODEC,
            &FAILED_CONTAINER,
            &FAILED_CORRUPT,
            &FAILED_FILE,
            &FAILED_FILE_MISSING,
            &FAILED_FILE_PERMISSIONS,
            &FAILED_FILE_NOT_RECOGNIZED,
            &FAILED_HARDWARE,
            &FAILED_INVALID_AUDIO_CHANNELS,
            &FAILED_INVALID_AUDIO_STREAMS,
            &FAILED_INVALID_DURATION_SS,
            &FAILED_INVALID_DURATION_TO,
            &FAILED_INVALID_ENCODER,
            &FAILED_JSON_PARSE,
            &FAILED_SYSTEM,
            &FINISHED,
            &STATISTICS,
            &WAITING,
            &WAITING_CONVERT,
            &WAITING_STATISTICS,
            &WAITING_VALIDATE,
            &VALIDATE};
  };

  static const StringEnumDataHolder<Activity> getKey(std::string value) {
    for (auto& item : _all()) {
      if (item->getName() == value) {
        return *item;
      }
    }
    return FAILED_SYSTEM;
  }
};

#endif  // !ACTIVITY_H
