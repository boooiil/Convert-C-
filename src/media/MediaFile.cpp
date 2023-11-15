#include "MediaFile.h"

MediaFile::MediaFile()
    : modifiedFileName(""),
      modifiedFileNameExt(""),
      conversionName(""),
      conversionPath(""),
      renamePath(""),
      series(""),
      path(""),
      ext(""),
      number(0),
      newSize(0),
      validationSize(0),
      quality(0),
      season(0) {}

MediaFile::~MediaFile() {}