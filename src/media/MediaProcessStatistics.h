#ifndef MEDIA_PROCESS_STATISTICS
#define MEDIA_PROCESS_STATISTICS

#include "MediaProcess.h"
class MediaProcessStatistics : public MediaProcess {
 public:
  MediaProcessStatistics(Container&, Media&);
  ~MediaProcessStatistics();

  void start(std::string) override;
  void parse(std::string) override;
};

#endif  // !MEDIA_PROCESS_STATISTICS
