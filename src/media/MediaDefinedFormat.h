#ifndef MEDIA_DEFINED_FORMAT
#define MEDIA_DEFINED_FORMAT

#include <string>
#include <unordered_map>

#include "MediaFormat.h"

class MediaDefinedFormat {
 public:
  MediaDefinedFormat();
  ~MediaDefinedFormat();

  static void addCustomFormat(int);

  static std::unordered_map<std::string, MediaFormat> formats;
};

#endif  // !MEDIA_DEFINED_FORMAT
