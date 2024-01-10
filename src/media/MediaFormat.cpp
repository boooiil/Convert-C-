#include "MediaFormat.h"

#include <cmath>

MediaFormat::MediaFormat()
    : name(""),
      crf(0),
      bitrate(0),
      min(0),
      max(0),
      width(0),
      height(0),
      crop(""),
      scale("") {}

MediaFormat::MediaFormat(std::string name, int crf, double bitrate, double min,
                         double max, int width, int height, std::string crop,
                         std::string scale)
    : name(name),
      crf(crf),
      bitrate(bitrate),
      min(min),
      max(max),
      width(width),
      height(height),
      crop(crop),
      scale(scale) {}

MediaFormat::~MediaFormat() {}

int MediaFormat::getGCD(int a, int b) {
  if (b == 0) {
    return a;
  }
  return getGCD(b, a % b);
}

int MediaFormat::getResolution(int width, int height, int newWidth) {
  int newHeight =
      static_cast<int>(ceil(static_cast<double>(height) / width * newWidth));
  return newHeight % 2 == 0 ? newHeight : newHeight + 1;
}