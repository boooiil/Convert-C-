#include "MediaDefinedFormat.h"

std::unordered_map<std::string, MediaFormat> MediaDefinedFormat::formats = {

    {"2160p", MediaFormat("2160p", 24, 30, 30, 40, 3840, 2160, "3840:1600",
                          "3840: 2160")},
    {"1440p", MediaFormat("1440p", 24, 20, 20, 27, 2560, 1440, "2560:1068",
                          "2560:1440")},
    {"1080p", MediaFormat("1080p", 24, 2.0, 1.6, 2.2, 1920, 1080, "1920:800",
                          "1920:1080")},
    {"1080pm", MediaFormat("1080pm", 24, 2.0, 1.6, 2.2, 1920, 1080, "1920:870",
                           "1920:1080")},
    {"1080pn", MediaFormat("1080pn", 24, 2.0, 1.6, 2.2, 1920, 1080, "1920:960",
                           "1920:1080")},
    {"720p",
     MediaFormat("720p", 24, 1.4, 1.2, 1.8, 1280, 720, "1280:534", "1280:720")},
    {"720pm", MediaFormat("720pm", 24, 1.4, 1.2, 1.8, 1280, 720, "1280:580",
                          "1280:720")},
    {"720pn", MediaFormat("720pn", 24, 1.4, 1.2, 1.8, 1280, 720, "1280:640",
                          "1280:720")},
    {"480p",
     MediaFormat("480p", 24, 0.6, 0.4, 0.8, 854, 480, "854:356", "854:480")},
    {"480pc",
     MediaFormat("480pc", 24, 0.6, 0.4, 0.8, 1138, 640, "854:720", "1138:640")}

};

MediaDefinedFormat::MediaDefinedFormat() {}
MediaDefinedFormat::~MediaDefinedFormat() {}

void MediaDefinedFormat::addCustomFormat(int height) {
  MediaFormat format =
      MediaFormat(std::to_string(height) + "p", 24, 0, 0, 0, 0, 0, "", "");

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

  // TODO: test this
};