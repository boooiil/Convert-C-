#include "MediaDefinedFormat.h"

#include <cmath>

std::unordered_map<std::string, MediaFormat> MediaDefinedFormat::formats = {

    {"2160p", MediaFormat("2160p", 24, 30.0f, 30.0f, 40.0f, 3840, 2160,
                          "3840:1600", "3840: 2160")},
    {"1440p", MediaFormat("1440p", 24, 20.0f, 20.0f, 27.0f, 2560, 1440,
                          "2560:1068", "2560:1440")},
    {"1080p", MediaFormat("1080p", 24, 2.0f, 1.6f, 2.2f, 1920, 1080, "1920:800",
                          "1920:1080")},
    {"1080pm", MediaFormat("1080pm", 24, 2.0f, 1.6f, 2.2f, 1920, 1080,
                           "1920:870", "1920:1080")},
    {"1080pn", MediaFormat("1080pn", 24, 2.0f, 1.6f, 2.2f, 1920, 1080,
                           "1920:960", "1920:1080")},
    {"720p", MediaFormat("720p", 24, 1.4f, 1.2f, 1.8f, 1280, 720, "1280:534",
                         "1280:720")},
    {"720pm", MediaFormat("720pm", 24, 1.4f, 1.2f, 1.8f, 1280, 720, "1280:580",
                          "1280:720")},
    {"720pn", MediaFormat("720pn", 24, 1.4f, 1.2f, 1.8f, 1280, 720, "1280:640",
                          "1280:720")},
    {"480p",
     MediaFormat("480p", 24, 0.6f, 0.4f, 0.8f, 854, 480, "854:356", "854:480")},
    {"480pc", MediaFormat("480pc", 24, 0.6f, 0.4f, 0.8f, 1138, 640, "854:720",
                          "1138:640")}

};

void MediaDefinedFormat::addCustomFormat(int height) {
  MediaFormat format = MediaFormat(std::to_string(height) + "p", 24, 0.0f, 0.0f,
                                   0.0f, 0, 0, "", "");

  format.height = height % 2 ? height++ : height;
  format.width = static_cast<int>(ceil(format.height * 1.777777777777778));

  if (format.width % 2) {
    format.width++;
  }

  int cropHeight = static_cast<int>(ceil(format.width / 2.4));

  if (cropHeight % 2) {
    cropHeight++;
  }

  format.crop = std::to_string(format.width) + ":" + std::to_string(cropHeight);
  format.scale =
      std::to_string(format.width) + ":" + std::to_string(format.height);

  MediaDefinedFormat::formats[format.name] = format;
};