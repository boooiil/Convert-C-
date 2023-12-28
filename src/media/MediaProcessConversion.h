#ifndef MEDIA_PROCESS_CONVERSION
#define MEDIA_PROCESS_CONVERSION

#include "MediaProcess.h"
class MediaProcessConversion : public MediaProcess {
 public:
  MediaProcessConversion(Container&, Media&);
  ~MediaProcessConversion();

  void parse(std::string) override;
};

#endif  // !MEDIA_PROCESS_CONVERSION
