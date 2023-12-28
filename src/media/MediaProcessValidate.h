#ifndef MEDIA_PROCESS_VALIDATE
#define MEDIA_PROCESS_VALIDATE

#include "MediaProcess.h"
class MediaProcessValidate : public MediaProcess {
  MediaProcessValidate(Container&, Media&);
  ~MediaProcessValidate();

  void parse(std::string) override;
};

#endif  // !MEDIA_PROCESS_VALIDATE
