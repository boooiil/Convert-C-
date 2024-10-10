#include "Quality.h"

#include <string>

#include "../../../../utils/RegexUtils.h"
#include "../../../../utils/StringUtils.h"
#include "../../../../utils/logging/Logger.h"
#include "../../../child/media/MediaDefinedFormat.h"
#include "../../../child/media/MediaFormat.h"
#include "../BaseArgument.h"

Quality::Quality(void)
    : BaseArgument<MediaFormat>("-q", "--quality", "Quality",
                                MediaDefinedFormat::formats["720p"]) {};
Quality::~Quality(void) {}

void Quality::parse(std::string provided) {
  LOG_DEBUG("Parsing quality:", provided);
  if (MediaDefinedFormat::formats.find(provided) !=
      MediaDefinedFormat::formats.end()) {
    value = MediaDefinedFormat::formats[provided];
  } else if (RegexUtils::isMatch(provided, "[0-9]+p")) {
    std::string quality_str = StringUtils::replaceAll(provided, "p", "");
    int quality = std::stoi(quality_str);

    MediaFormat mf = MediaFormat();
    mf.fromCustom(quality);

    value = mf;
  } else {
    this->setErrored(true);
  }
}

const std::string Quality::toString(void) const { return this->value.name; }

// there will always be a defined format
const bool Quality::hasData(void) const { return true; }
