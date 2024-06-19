#include "./Quality.h"

#include "../../../logging/Log.h"
#include "../../../media/MediaDefinedFormat.h"
#include "../../../utils/RegexUtils.h"
#include "../../../utils/StringUtils.h"

Quality::Quality(void) : BaseArgument<MediaFormat>() {
  value = MediaDefinedFormat::formats["720p"];
  helpMessage = "Quality of the video.";
};
Quality::~Quality(void) {}

void Quality::parse(std::string provided) {
  Log::debug({"[Quality] Parsing quality:", provided});
  if (MediaDefinedFormat::formats.find(provided) !=
      MediaDefinedFormat::formats.end()) {
    value = MediaDefinedFormat::formats[provided];
  } else if (RegexUtils::isMatch(provided, "[0-9]+p")) {
    std::string quality_str = StringUtils::replaceAll(provided, "p", "");
    int quality = std::stoi(quality_str);

    MediaDefinedFormat::addCustomFormat(quality);
    value = MediaDefinedFormat::formats[provided];
  } else {
    errored = true;
  }
}

Quality& Quality::operator=(const MediaFormat& provided) {
  value = provided;
  return *this;
}