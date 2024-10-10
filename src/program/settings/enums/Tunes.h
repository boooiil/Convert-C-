#ifndef TUNES_H
#define TUNES_H

#include <string>
#include <vector>

#include "StringEnumDataHolder.h"

class Tunes {
 public:
  static const StringEnumDataHolder<Tunes> DEFAULT;
  static const StringEnumDataHolder<Tunes> FILM;
  static const StringEnumDataHolder<Tunes> ANIMATION;
  static const StringEnumDataHolder<Tunes> GRAIN;
  static const StringEnumDataHolder<Tunes> STILL_IMAGE;
  static const StringEnumDataHolder<Tunes> PSNR;
  static const StringEnumDataHolder<Tunes> SSIM;
  static const StringEnumDataHolder<Tunes> FAST_DECODE;
  static const StringEnumDataHolder<Tunes> ZERO_LATENCY;
  static const StringEnumDataHolder<Tunes> TEXTURE_COMPRESSION;
  static const StringEnumDataHolder<Tunes> PROXY;
  static const StringEnumDataHolder<Tunes> HIGH_QUALITY;
  static const StringEnumDataHolder<Tunes> LOW_QUALITY;
  static const StringEnumDataHolder<Tunes> ZERO_LATENCY_LOW_LATENCY;
  static const StringEnumDataHolder<Tunes> LOSSLESS;

  static const std::vector<const StringEnumDataHolder<Tunes>*> _all() {
    return {&DEFAULT,      &FILM,
            &ANIMATION,    &GRAIN,
            &STILL_IMAGE,  &PSNR,
            &SSIM,         &FAST_DECODE,
            &ZERO_LATENCY, &TEXTURE_COMPRESSION,
            &PROXY,        &HIGH_QUALITY,
            &LOW_QUALITY,  &ZERO_LATENCY_LOW_LATENCY,
            &LOSSLESS};
  }

  static const StringEnumDataHolder<Tunes> getKey(std::string value) {
    for (auto& item : _all()) {
      if (item->getName() == value) {
        return *item;
      }
    }
    return DEFAULT;
  }
};

#endif  // TUNES_H