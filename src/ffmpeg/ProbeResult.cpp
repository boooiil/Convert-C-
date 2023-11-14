#include "ProbeResult.h"

#include <iostream>

#include "ProbeResultStreamAudio.h"
#include "ProbeResultStreamSubtitle.h"
#include "ProbeResultStreamVideo.h"

/** This constructor should not be used. */
ProbeResult::ProbeResult(){};
ProbeResult::~ProbeResult(){};

ProbeResult::ProbeResult(nlohmann::json JSON) {
  ProbeResult::format = ProbeResultFormat(JSON["format"]);

  for (nlohmann::json stream : JSON["streams"]) {
    if (stream["codec_type"] == "video") {
      ProbeResult::streams.push_back(ProbeResultStreamVideo(stream));
    } else if (stream["codec_type"] == "audio") {
      ProbeResult::streams.push_back(ProbeResultStreamAudio(stream));
    } else if (stream["codec_type"] == "subtitle") {
      ProbeResult::streams.push_back(ProbeResultStreamSubtitle(stream));
    }
  }
}