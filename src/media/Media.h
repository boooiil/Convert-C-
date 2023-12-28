#ifndef MEDIA
#define MEDIA

#include <string>
#include <vector>

#include "../application/Activity.h"
#include "MediaFile.h"
#include "MediaVideoProperties.h"
#include "MediaWorkingProperties.h"

class Media {
 public:
  Activity::ActivityType activity = Activity::WAITING;
  // cwd path
  std::string path;
  // original filename
  std::string name;
  std::vector<std::string> ffmpegArguments;
  long started;
  long ended;

  MediaFile file;
  MediaVideoProperties video;
  MediaWorkingProperties working;

  Media();
  Media(std::string, std::string);
  ~Media();

  void doStatistics(class Container*);
  void doConversion(class Container*);
  void doValidation(class Container*);

  void buildFFmpegArguments(class Container*, bool);
  void rename(class Container*);

  bool isProcessing();

 private:
  void resolvePath(std::string, std::string);
  void resolveExtension(std::string);
  void resolveSeries(std::string);
  void resolveSeason(std::string);
  void resolveEpisode(std::string);
  void resolveQuality(std::string);
  void resolveModifiedFileName(std::string, std::string, std::string,
                               std::string);
  void resolveModifiedFileNameExt(std::string, std::string);
  void resolveRenamePath(std::string, std::string, std::string);
  void resolveConversionName(std::string, std::string);
  void resolveConversionPath(std::string, std::string, std::string,
                             std::string);
};

#endif  // !MEDIA
