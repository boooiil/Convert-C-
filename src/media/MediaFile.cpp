#include "MediaFile.h"

MediaFile::MediaFile()
    : modifiedFileName(""),
      modifiedFileNameExt(""),
      conversionName(""),
      conversionPath(""),
      renamePath(""),
      episode(""),
      series(""),
      path(""),
      ext(""),
      number(0),
      size(0),
      newSize(0),
      validationSize(0),
      quality(0),
      season(0) {}

MediaFile::~MediaFile() {}