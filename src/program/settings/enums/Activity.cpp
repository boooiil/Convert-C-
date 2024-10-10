#include "Activity.h"

#include "StringEnumDataHolder.h"

const StringEnumDataHolder<Activity> Activity::CONVERT("convert", "Convert");
const StringEnumDataHolder<Activity> Activity::FAILED("failed", "Failed");
const StringEnumDataHolder<Activity> Activity::FAILED_CODEC("failed_codec",
                                                            "Failed Codec");
const StringEnumDataHolder<Activity> Activity::FAILED_CONTAINER(
    "failed_container", "Failed Container");
const StringEnumDataHolder<Activity> Activity::FAILED_CORRUPT("failed_corrupt",
                                                              "Failed Corrupt");
const StringEnumDataHolder<Activity> Activity::FAILED_FILE("failed_file",
                                                           "Failed File");
const StringEnumDataHolder<Activity> Activity::FAILED_FILE_MISSING(
    "failed_file_missing", "Failed File Missing");
const StringEnumDataHolder<Activity> Activity::FAILED_FILE_PERMISSIONS(
    "failed_file_permissions", "Failed File Permissions");
const StringEnumDataHolder<Activity> Activity::FAILED_FILE_NOT_RECOGNIZED(
    "failed_file_not_recognized", "Failed File Not Recognized");
const StringEnumDataHolder<Activity> Activity::FAILED_HARDWARE(
    "failed_hardware", "Failed Hardware");
const StringEnumDataHolder<Activity> Activity::FAILED_INVALID_AUDIO_CHANNELS(
    "failed_invalid_audio_channels", "Failed Invalid Audio Channels");
const StringEnumDataHolder<Activity> Activity::FAILED_INVALID_AUDIO_STREAMS(
    "failed_invalid_audio_streams", "Failed Invalid Audio Streams");
const StringEnumDataHolder<Activity> Activity::FAILED_INVALID_DURATION_SS(
    "failed_invalid_duration_ss", "Failed Invalid Duration SS");
const StringEnumDataHolder<Activity> Activity::FAILED_INVALID_DURATION_TO(
    "failed_invalid_duration_to", "Failed Invalid Duration TO");
const StringEnumDataHolder<Activity> Activity::FAILED_INVALID_ENCODER(
    "failed_invalid_encoder", "Failed Invalid Encoder");
const StringEnumDataHolder<Activity> Activity::FAILED_JSON_PARSE(
    "failed_json_parse", "Failed JSON Parse");
const StringEnumDataHolder<Activity> Activity::FAILED_SYSTEM("failed_system",
                                                             "Failed System");
const StringEnumDataHolder<Activity> Activity::FINISHED("finished", "Finished");
const StringEnumDataHolder<Activity> Activity::STATISTICS("statistics",
                                                          "Statistics");
const StringEnumDataHolder<Activity> Activity::WAITING("waiting", "Waiting");
const StringEnumDataHolder<Activity> Activity::WAITING_CONVERT(
    "waiting_convert", "Waiting Convert");
const StringEnumDataHolder<Activity> Activity::WAITING_STATISTICS(
    "waiting_statistics", "Waiting Statistics");
const StringEnumDataHolder<Activity> Activity::WAITING_VALIDATE(
    "waiting_validate", "Waiting Validate");
const StringEnumDataHolder<Activity> Activity::VALIDATE("validate", "Validate");
