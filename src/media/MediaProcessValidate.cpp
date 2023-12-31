#include "MediaProcessValidate.h"

MediaProcessValidate::MediaProcessValidate(Container& container, Media& media)
    : MediaProcess(container, media) {}

MediaProcessValidate::~MediaProcessValidate() { MediaProcess::~MediaProcess(); }

void MediaProcessValidate::parse(std::string data) {
  // TODO: implement this
}