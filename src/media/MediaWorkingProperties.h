#ifndef MEDIA_WORKING_PROPERTIES
#define MEDIA_WORKING_PROPERTIES

#include <string>
class MediaWorkingProperties {
 public:
  MediaWorkingProperties();
  ~MediaWorkingProperties();

  float quality;
  float bitrate;
  float fps;

  int completedFrames;
};

#endif  // !MEDIA_WORKING_PROPERTIES
