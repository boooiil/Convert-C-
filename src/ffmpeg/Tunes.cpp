#include "./Tunes.h"

#include "../utils/StringUtils.h"

std::unordered_map<Tunes::Tune, std::string> Tunes::tuneMap = {
    {Tunes::FILM, "film"},
    {Tunes::ANIMATION, "animation"},
    {Tunes::GRAIN, "grain"},
    {Tunes::STILL_IMAGE, "still_image"},
    {Tunes::PSNR, "psnr"},
    {Tunes::SSIM, "ssim"},
    {Tunes::FAST_DECODE, "fast_decode"},
    {Tunes::ZERO_LATENCY, "zero_latency"},
    {Tunes::TEXTURE_COMPRESSION, "texture_compression"},
    {Tunes::PROXY, "proxy"},
    {Tunes::HIGH_QUALITY, "high_quality"},
    {Tunes::LOW_LATENCY, "low_latency"},
    {Tunes::ZERO_LATENCY_LOW_LATENCY, "zero_latency_low_latency"},
    {Tunes::LOSSLESS, "lossless"},
    {Tunes::DEFAULT, "default"}};

Tunes::Tunes() {}
Tunes::~Tunes() {}

Tunes::Tune Tunes::getKey(std::string value) {
  value = StringUtils::toLowerCase(value);
  for (std::pair<Tunes::Tune, std::string> tune : tuneMap) {
    if (tune.second == value) {
      return tune.first;
    }
  }
  return Tunes::DEFAULT;
}

std::string Tunes::getValue(Tunes::Tune tune) { return tuneMap.at(tune); }