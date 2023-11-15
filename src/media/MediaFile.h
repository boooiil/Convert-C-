#ifndef MEDIA_FILE
#define MEDIA_FILE

#include <string>

class MediaFile {
 public:
  MediaFile();
  ~MediaFile();

  std::string modifiedFileName;
  std::string modifiedFileNameExt;
  std::string conversionName;
  std::string conversionPath;
  std::string renamePath;
  std::string series;
  std::string path;
  std::string ext;

  int number;
  int newSize;
  int validationSize;
  int quality;
  int season;
};

#endif  // !MEDIA_FILE
