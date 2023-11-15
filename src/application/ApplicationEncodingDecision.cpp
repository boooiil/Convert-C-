#include "ApplicationEncodingDecision.h"

ApplicationEncodingDecision::ApplicationEncodingDecision()
    : quality("720p"),
      amount(1),
      crfOverride(0),
      crop(false),
      useBitrate(false),
      useConstrain(false),
      validate(false),
      useHardwareDecode(false),
      useHardwareEncode(false),
      overwrite(false) {}
ApplicationEncodingDecision::~ApplicationEncodingDecision() {}

void ApplicationEncodingDecision::validateSettings() {
  if (ApplicationEncodingDecision::tune == "film" &&
      ApplicationEncodingDecision::wantedEncoder.find_first_of("hevc")) {
    ApplicationEncodingDecision::tune = "";
  }
}