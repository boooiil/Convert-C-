#ifndef MEDIA_VIDEO_PROPERTIES
#define MEDIA_VIDEO_PROPERTIES

#include <string>

class MediaVideoProperties {
 public:
  MediaVideoProperties();
  ~MediaVideoProperties();

  float fps;

  int totalFrames;
  int width;
  int height;
  int crf;

  std::string convertedResolution;
  std::string subtitleProvider;
  std::string convertedHeight;
  std::string convertedWidth;
  std::string ratio;
  std::string crop;
};

#endif  // !MEDIA_VIDEO_PROPERTIES
