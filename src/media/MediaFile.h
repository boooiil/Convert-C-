#ifndef MEDIA_FILE
#define MEDIA_FILE

#include <string>

class MediaFile {
 public:
  MediaFile();
  ~MediaFile();

  /* Filename after renaming without ext */
  std::string modifiedFileName;
  /* Filename after renaming including extension */
  std::string modifiedFileNameExt;
  /* Result of modifiedFileNameExt */
  std::string conversionName;
  /* Path resolving to cwd/{series} Season {##}/{conversionName} */
  std::string conversionPath;
  std::string renamePath;
  std::string episode;
  std::string series;
  std::string path;
  std::string ext;

  int number;
  int size;
  int newSize;
  int validationSize;
  int quality;
  int season;
};

#endif  // !MEDIA_FILE
