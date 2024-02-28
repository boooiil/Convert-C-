#include "ApplicationEncodingDecision.h"

#include "../media/MediaDefinedFormat.h"

ApplicationEncodingDecision::ApplicationEncodingDecision()
    : quality(MediaDefinedFormat::formats["720p"]),
      runningDecoder("cuda"),
      runningEncoder("hevc"),
      amount(1),
      crfOverride(0),
      crop(false),
      useBitrate(false),
      useConstrain(false),
      validate(false),
      useHardwareDecode(true),
      useHardwareEncode(false),
      overwrite(false),
      printInformation(false) {}
ApplicationEncodingDecision::~ApplicationEncodingDecision() {}

void ApplicationEncodingDecision::validateSettings() {
  if (ApplicationEncodingDecision::tune == "film" &&
      ApplicationEncodingDecision::wantedEncoder.find_first_of("hevc")) {
    ApplicationEncodingDecision::tune = "";
  }
}