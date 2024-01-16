#include "MediaWorkingProperties.h"

#include "../logging/Log.h"

MediaWorkingProperties::MediaWorkingProperties()
    : quality(0.0), bitrate(0.0), fps(0.0), completedFrames(0) {}

MediaWorkingProperties::~MediaWorkingProperties() {
  Log::debug(
      {"[MediaWorkingProperties.cpp] Deconstructing MediaWorkingProperties"});
}