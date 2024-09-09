#include "MediaProcessConversion.h"

#include <regex>
#include <stdexcept>
#include <string>

#include "../../../logging/Log.h"
#include "../../../utils/RegexUtils.h"
#include "../../Program.h"
#include "../../settings/ProgramSettings.h"
#include "../../settings/arguments/ArgumentParser.h"
#include "../../settings/enums/Activity.h"
#include "../../settings/enums/Encoders.h"
#include "Media.h"
#include "MediaProcess.h"

MediaProcessConversion::MediaProcessConversion(Media* media)
    : MediaProcess(media) {}

MediaProcessConversion::~MediaProcessConversion() {
  MediaProcess::~MediaProcess();
}

void MediaProcessConversion::parse(std::string data) {
  Log::debug({"[MediaProcessConversion.cpp] PARSING LINE:", data});

  ArgumentParser argumentParser = *Program::settings->argumentParser;
  ProgramSettings programSettings = *Program::settings->programSettings;

  // Return fail IF:
  // 1&2. Encode fails to find a device
  // 3. Encode fails to load nvcuda.dll
  // 4. Encode fails to find an nvidia device
  if (RegexUtils::isMatch(data, "openencodesessionex failed: out of memory",
                          std::regex::icase) ||
      RegexUtils::isMatch(data, "no capable devices found",
                          std::regex::icase) ||
      RegexUtils::isMatch(data, "cannot load nvcuda.dll", std::regex::icase) ||
      RegexUtils::isMatch(data, "device type cuda needed for codec",
                          std::regex::icase)) {
    // if the user wants to use hardware encoding (nvenc, amf, qsv)
    if (argumentParser.useHardwareEncode) {
      this->media->setActivity(Activity::FAILED_HARDWARE);
    } else if (Encoders::isHardwareEncoder(programSettings.runningEncoder)) {
      this->media->setActivity(Activity::FAILED_HARDWARE);
    } else
      throw std::runtime_error(
          "Out of memory even though hardware encoding is disabled. This "
          "should not happen.");
  }

  // If the file is already encoded, set the process status to validating
  else if (RegexUtils::isMatch(data, "already exists", std::regex::icase)) {
    this->media->setActivity(Activity::WAITING_VALIDATE);
  } else if (RegexUtils::isMatch(data, "no such file", std::regex::icase)) {
    this->media->setActivity(Activity::FAILED_FILE_MISSING);
  } else if (RegexUtils::isMatch(data, "matches no streams",
                                 std::regex::icase)) {
    this->media->setActivity(Activity::FAILED_INVALID_AUDIO_STREAMS);
  } else if (RegexUtils::isMatch(data, "frame=.+?(\\d+)")) {
    Log::debug({"[MediaProcessConversion.cpp] PARSING LINE"});

    std::string quality =
        RegexUtils::getFirstMatch(data, "q=(\\d+\\.\\d+|-\\d+\\.\\d+)");
    std::string bitrate =
        RegexUtils::getFirstMatch(data, "bitrate= ?(\\d+\\.\\d+)");
    std::string completedFrames =
        RegexUtils::getFirstMatch(data, "frame=.+?(\\d+)");
    std::string fps =
        RegexUtils::getFirstMatch(data, "fps=.+?(\\d+\\.\\d+|\\d+)");
    ;

    if (quality == "") quality = "-1.0";
    if (bitrate == "") bitrate = "-1.0";
    if (completedFrames == "") completedFrames = "-1";
    if (fps == "") fps = "-1.0";

    // assert(quality != "");
    // assert(bitrate != "");
    // assert(size != "");
    // assert(completedFrames != "");
    // assert(fps != "");

    if (quality != "-1.0") this->media->working->quality = std::stof(quality);
    this->media->working->bitrate = std::stof(bitrate);
    this->media->working->completedFrames = std::stoll(completedFrames);
    this->media->working->fps = std::stof(fps);

    Log::debug({"[MediaProcessConversion.cpp] QUALITY:", quality});
    Log::debug({"[MediaProcessConversion.cpp] BITRATE:", bitrate});
    Log::debug(
        {"[MediaProcessConversion.cpp] COMPLETED FRAMES:", completedFrames});
    Log::debug({"[MediaProcessConversion.cpp] FPS:", fps});
  }

  Log::debug({"[MediaProcessConversion.cpp] PARSING END"});
}