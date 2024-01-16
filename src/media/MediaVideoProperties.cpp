#include "MediaVideoProperties.h"

#include "../logging/Log.h"

MediaVideoProperties::MediaVideoProperties()
    : fps(0.0),
      totalFrames(0),
      width(0),
      height(0),
      crf(0),
      convertedResolution(""),
      subtitleProvider(""),
      convertedHeight(""),
      convertedWidth(""),
      ratio(""),
      crop("") {}

MediaVideoProperties::~MediaVideoProperties() {
  Log::debug(
      {"[MediaVideoProperties.cpp] Deconstructing MediaVideoProperties"});
}