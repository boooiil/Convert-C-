#include "MediaProcessConversion.h"

MediaProcessConversion::MediaProcessConversion(Container& container,
                                               Media& media)
    : MediaProcess(container, media) {}

MediaProcessConversion::~MediaProcessConversion() {
  MediaProcess::~MediaProcess();
}

void MediaProcessConversion::parse(std::string data) {
  // TODO: implement this
}