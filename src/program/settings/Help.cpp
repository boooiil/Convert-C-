#include "Help.h"

#include "../../logging/Log.h"

void Help::printHelp() {
  Log::send(
      {"Usage: convert [options]\n\n",
       "Options:\n",
       "  -a    --amount [num]                 Set the amount of files to "
       "convert at once (default: 1).\n",
       "  -as   --audiostreams [as0,as1...]    Set the audio stream indexes "
       "to include in the conversion (default: all).\n",
       "  -b,   --bitrate                      Use the defined bitrate "
       "instead of CRF (default: false).\n",
       "  -c,   --crop                         Use the defined crop.\n",
       "  -co,  --constrain                    Attempt to constrain the "
       "bitrate (default: false).\n",
       "  -crf, --crf [num]                    Set the CRF value.\n",
       "  -e,   --encoder [encoder]            Set the encoder to use.\n",
       "  -h,   --help                         Show this help message and "
       "exit.\n",
       "  -hwd, --hardwaredecode               Use hardware decoding (default: "
       "true).\n",
       "  -hwe, --hardwareencode               Use hardware encoding (default: "
       "false).\n",
       "  -o,   --overwrite                    Overwrite existing files "
       "(default: false).\n",
       "  -t,   --tune [tune]                  Set the tune (default: film "
       "(x264), none (x265).\n",
       "  -tr,  --trim [hh:mm:ss,hh:mm:ss]     Trim the media between "
       "the given timestamps\n\n",

       "Resolutions:\n",
       "  Custom:\n",
       "    <value>p\n",
       "      CRF: 24\n",
       "      Bitrate: NULL\n",
       "      MIN: NULL\n",
       "      MAX: NULL\n",
       "      WIDTH: CALCULATED\n",
       "      HEIGHT: PROVIDED\n",
       "      CROP: CALCULATED\n\n",
       "  Configured:\n",
       "    2160p\n",
       "      CRF: 24\n",
       "      Bitrate: 30M\n",
       "      MIN: 30M\n",
       "      MAX: 40M\n",
       "      WIDTH: 3840\n",
       "      HEIGHT: 2160\n",
       "      CROP: 3840:1600 (2.40:1 ~ 21:9)\n"
       "    1440p\n",
       "      CRF: 24\n",
       "      Bitrate: 20M\n",
       "      MIN: 20M\n",
       "      MAX: 27M\n",
       "      WIDTH: 2560\n",
       "      HEIGHT: 1440\n",
       "      CROP: 2560:1066 (2.40:1 ~ 21:9)\n"
       "    1080p\n",
       "      CRF: 24\n",
       "      Bitrate: 2M\n",
       "      MIN: 1.6M\n",
       "      MAX: 2.2M\n",
       "      WIDTH: 1920\n",
       "      HEIGHT: 1080\n",
       "      CROP: 1920:800 (2.40:1 ~ 21:9)\n"
       "    1080pn (Traditional TV/Netflix Cropping)\n",
       "      CRF: 24\n",
       "      Bitrate: 2M\n",
       "      MIN: 1.6M\n",
       "      MAX: 2.2M\n",
       "      WIDTH: 1920\n",
       "      HEIGHT: 1080\n",
       "      CROP: 1920:960 (2:1)\n"
       "    1080pm (Some Marvel Croppings)\n",
       "      CRF: 24\n",
       "      Bitrate: 2M\n",
       "      MIN: 1.6M\n",
       "      MAX: 2.2M\n",
       "      WIDTH: 1920\n",
       "      HEIGHT: 1080\n",
       "      CROP: 1920:870 (64:29)\n"
       "    720p\n",
       "      CRF: 24\n",
       "      Bitrate: 1.4M\n",
       "      MIN: 1.2M\n",
       "      MAX: 1.8M\n",
       "      WIDTH: 1280\n",
       "      HEIGHT: 720\n",
       "      CROP: 1280:534 (2.40:1 ~ 21:9)\n"
       "    720pn (Traditional TV/Netflix Cropping)\n",
       "      CRF: 24\n",
       "      Bitrate: 1.4M\n",
       "      MIN: 1.2M\n",
       "      MAX: 1.8M\n",
       "      WIDTH: 1280\n",
       "      HEIGHT: 720\n",
       "      CROP: 1280:640 (2:1)\n"
       "    720pm (Some Marvel Croppings)\n",
       "      CRF: 24\n",
       "      Bitrate: 1.4M\n",
       "      MIN: 1.2M\n",
       "      MAX: 1.8M\n",
       "      WIDTH: 1280\n",
       "      HEIGHT: 720\n",
       "      CROP: 1280:580 (64:29)\n"
       "    480p\n",
       "      CRF: 24\n",
       "      Bitrate: 600K\n",
       "      MIN: 400K\n",
       "      MAX: 800K\n",
       "      WIDTH: 854\n",
       "      HEIGHT: 480\n",
       "      CROP: 854:356 (2.40:1 ~ 21:9)\n"
       "    480pc (NTSC Cropping)\n",
       "      CRF: 24\n",
       "      Bitrate: 600K\n",
       "      MIN: 400K\n",
       "      MAX: 800K\n",
       "      WIDTH: 1138\n",
       "      HEIGHT: 640\n",
       "      CROP: 854:720 (32:27 ~ 4:3)\n"

      });
}
