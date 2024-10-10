#include "Tunes.h"

#include "StringEnumDataHolder.h"

const StringEnumDataHolder<Tunes> Tunes::DEFAULT("default", "Default");
const StringEnumDataHolder<Tunes> Tunes::FILM("film", "Film");
const StringEnumDataHolder<Tunes> Tunes::ANIMATION("animation", "Animation");
const StringEnumDataHolder<Tunes> Tunes::GRAIN("grain", "Grain");
const StringEnumDataHolder<Tunes> Tunes::STILL_IMAGE("still_image",
                                                     "Still Image");
const StringEnumDataHolder<Tunes> Tunes::PSNR("psnr", "PSNR");
const StringEnumDataHolder<Tunes> Tunes::SSIM("ssim", "SSIM");
const StringEnumDataHolder<Tunes> Tunes::FAST_DECODE("fast_decode",
                                                     "Fast Decode");
const StringEnumDataHolder<Tunes> Tunes::ZERO_LATENCY("zero_latency",
                                                      "Zero Latency");
const StringEnumDataHolder<Tunes> Tunes::TEXTURE_COMPRESSION(
    "texture_compression", "Texture Compression");
const StringEnumDataHolder<Tunes> Tunes::PROXY("proxy", "Proxy");
const StringEnumDataHolder<Tunes> Tunes::HIGH_QUALITY("high_quality",
                                                      "High Quality");
const StringEnumDataHolder<Tunes> Tunes::LOW_QUALITY("low_quality",
                                                     "Low Quality");
const StringEnumDataHolder<Tunes> Tunes::ZERO_LATENCY_LOW_LATENCY(
    "zero_latency_low_latency", "Zero Latency Low Latency");
const StringEnumDataHolder<Tunes> Tunes::LOSSLESS("lossless", "Lossless");