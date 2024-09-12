#include "ChildDisplay.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <string>

#include "../../../logging/Log.h"
#include "../../../logging/LogColor.h"
#include "../../../utils/NumberUtils.h"
#include "../../../utils/StringUtils.h"
#include "../../../utils/TimeUtils.h"
#include "../../Program.h"
#include "../../generics/GenericRunner.h"
#include "../../settings/ProgramSettings.h"
#include "../../settings/arguments/ArgumentParser.h"
#include "../../settings/enums/Activity.h"
#include "../../settings/enums/Encoders.h"
#include "../../settings/enums/HWAccelerators.h"
#include "../../settings/enums/LoggingOptions.h"
#include "../../settings/enums/Tunes.h"
#include "../../ticker/NTicker.h"
#include "../Child.h"
#include "../ffmpeg/ProbeResultStreamAudio.h"
#include "../ffmpeg/ProbeResultStreamSubtitle.h"
#include "../ffmpeg/ProbeResultStreamVideo.h"
#include "../media/Media.h"

void ChildDisplay::print(void) {
  Child child =
      *Program::ticker->getRunner<NTicker>()->runner->getRunner<Child>();
  ArgumentParser argumentParser = *Program::settings->argumentParser;
  ProgramSettings programSettings = *Program::settings->programSettings;
  std::string sendStr = "";

  // int bufferLen = static_cast<int>(child.converting.size()) +
  //                 static_cast<int>(child.pending.size()) + 1;

  std::string ob = LogColor::fgGray("[");
  std::string cb = LogColor::fgGray("]");

  std::string time = ob + LogColor::fgCyan("TIME") + cb + " " +
                     TimeUtils::dateFormat(TimeUtils::getEpoch());
  std::string encoder =
      ob + LogColor::fgCyan("TARGET ENC") + cb + " " +
      LogColor::fgGray(Encoders::getValue(argumentParser.wantedEncoder));
  std::string runningEncoder =
      ob + LogColor::fgCyan("ENC") + cb + " " +
      LogColor::fgGray(Encoders::getValue(programSettings.runningEncoder));
  std::string runningDecoder = ob + LogColor::fgCyan("ACC") + cb + " " +
                               LogColor::fgGray(HWAccelerators::getValue(
                                   programSettings.runningHWAccel));
  std::string resolution = ob + LogColor::fgCyan("RES") + cb + " " +
                           LogColor::fgGray(argumentParser.quality.get().name);
  std::string tune = ob + LogColor::fgCyan("TUNE") + cb + " " +
                     LogColor::fgGray(Tunes::getValue(argumentParser.tune));
  std::string amount = ob + LogColor::fgCyan("AMOUNT") + cb + " " +
                       LogColor::fgGray(std::to_string(argumentParser.amount));

  std::string constrain = ob + LogColor::fgRed("CONSTRAIN") + cb;
  std::string debug = ob + LogColor::fgRed("DEBUG") + cb;
  std::string crop = ob + LogColor::fgRed("CROP") + cb;

  std::string header = time + " " + encoder + " " + runningEncoder + " " +
                       runningDecoder + " " + resolution + " " + tune + " " +
                       amount;

  if (argumentParser.useConstrain) {
    header += " " + constrain;
  }

  if (argumentParser.loggingFormat == LoggingOptions::DEBUG) {
    header += " " + debug;
  }

  if (argumentParser.crop) {
    header += " " + crop;
  }

// clear console?
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
  sendStr += header + "\n";
  // Program::log->sendBuffer(bufferLen, header);

  std::queue<Media*> t_queue;

  while (!child.converting.empty()) {
    Media* media = child.converting.front();
    child.converting.pop();

    float mediaFPS = media->working->fps > 0 ? media->working->fps : 1;
    double totalFrames = static_cast<double>(media->video->totalFrames);
    double completedFrames = static_cast<double>(media->working->completedFrames);

    int eta_result = static_cast<int>(
        ceil((totalFrames - completedFrames) / mediaFPS) * 1000);

    int percent_result =
      static_cast<int>(std::round((completedFrames / totalFrames) * 100));
    

    // create a time util to get this
    std::string started = ob + LogColor::fgCyan("START") + cb + " " +
                          TimeUtils::timeFormat(media->started);
    // create a time util to get this
    std::string eta = ob + LogColor::fgCyan("ETA") + cb + " " +
                      TimeUtils::durationFormat(eta_result);

    float crf = media->working->quality;
    int v_crf = media->video->crf;

    float workingFPS = media->working->fps;
    float videoFPS = media->video->fps;

    std::string fileName = ob + LogColor::fgCyan("FILE") + cb + " " +
                           LogColor::fgGray(StringUtils::truncateString(
                               media->file->conversionName, 25));

    std::string activity = ob + LogColor::fgCyan("ACT") + cb + " " +
                           Activity::getValue(media->getActivity());

    std::string percent =
      ob + LogColor::fgCyan("PROG") + cb + " " +
      std::to_string(percent_result) +
        "%";

    std::string cq = ob + LogColor::fgCyan("QUAL") + cb + " " +
                     NumberUtils::formatNumber((v_crf / crf) * 100, 2) + "%";
    std::string speed = ob + LogColor::fgCyan("SPEED") + cb + " " +
                        NumberUtils::formatNumber(workingFPS / videoFPS, 2);

    std::string bitrate =
        ob + LogColor::fgCyan("BITRATE") + cb + " " +
        NumberUtils::formatNumber(media->working->bitrate, 2) + "kb/s";

    sendStr += fileName + " " + activity + " " + started + " " + percent + " " +
               cq + " " + bitrate + " " + speed + " " + eta + "\n";
    // Program::log->sendBuffer(
    //     bufferLen, fileName + " " + activity + " " + started + " " + percent
    //     + " " + cq + " " + bitrate + " " + speed + " " + eta);

    t_queue.push(media);
  }

  child.converting = t_queue;
  t_queue = std::queue<Media*>();

  while (!child.pending.empty()) {
    Media* media = child.pending.front();
    child.pending.pop();

    std::string fileName = ob + LogColor::fgCyan("FILE") + cb + " " +
                           LogColor::fgGray(StringUtils::truncateString(
                               media->file->conversionName, 25));

    std::string activity = ob + LogColor::fgCyan("ACT") + cb + " " +
                           Activity::getValue(media->getActivity());

    if (media->hasFinished()) {
      double currSize = static_cast<double>(media->file->size);
      double newSize = static_cast<double>(media->file->newSize);

      int calculatedSize =
          static_cast<int>(std::round(((currSize - newSize) / currSize) * 100));

      std::string ended = ob + LogColor::fgCyan("END") + cb + " " +
                          TimeUtils::timeFormat(media->ended);
      std::string elapsed =
          ob + LogColor::fgCyan("ELAPSED") + cb + " " +
          TimeUtils::durationFormat((media->ended - media->started) * 1000);

      std::string reduced = ob + LogColor::fgCyan("REDUCED") + cb + " " +
                            std::to_string(calculatedSize) + "%";

      sendStr += fileName + " " + activity + " " + reduced + " " + ended + " " +
                 elapsed + "\n";
      // Program::log->sendBuffer(bufferLen, fileName + " " + activity + " " +
      //                                         reduced + " " + ended + " " +
      //                                         elapsed);
    } else {
      sendStr += fileName + " " + activity + "\n";
      // Program::log->sendBuffer(bufferLen, fileName + " " + activity);
    }

    t_queue.push(media);
  }
  child.pending = t_queue;
  Log::send({sendStr});
}

void ChildDisplay::printDebug(void) {
  // TODO: finish
}

void ChildDisplay::printInformation(void) {
  Log::debug({"Printing Information"});

  NTicker* ticker = Program::ticker->getRunner<NTicker>();
  Child* runner = ticker->runner->getRunner<Child>();

  Log::debug({
      LogColor::fgBlack("Black"),
      LogColor::fgRed("Red"),
      LogColor::fgGreen("Green"),
      LogColor::fgGray("Gray"),
      LogColor::fgYellow("Yellow"),
      LogColor::fgBlue("Blue"),
      LogColor::fgOrange("Orange"),
      LogColor::fgMagenta("Magenta"),
      LogColor::fgCyan("Cyan"),
      LogColor::fgWhite("White"),
  });

  if (runner->pending.empty()) {
    Log::send({LogColor::fgRed("No media files found.")});
    return;
  }

  std::queue<Media*> t_queue;

  while (!runner->pending.empty()) {
    Media* media = runner->pending.front();
    runner->pending.pop();

    media->doStatistics();
    media->buildFFmpegArguments(false);

    std::string nl = "\n";
    std::string ob = LogColor::fgGray("[");
    std::string cb = LogColor::fgGray("]");
    std::string colon = LogColor::fgGray(": ");

    Log::send({nl + ob + LogColor::fgRed(media->file->originalFileNameExt) +
               cb + nl});

    Log::send({LogColor::fgWhite("  " + ob + "Format") + cb});

    Log::send({LogColor::bgBlue("    Duration") + colon +
               LogColor::bgOrange(media->probeResult->format.duration)});

    Log::send({LogColor::bgBlue("    Format: ") +
               LogColor::bgOrange(media->probeResult->format.format_name)});

    Log::send({LogColor::bgBlue("    Bit Rate: ") +
               LogColor::bgOrange(media->probeResult->format.bit_rate)});

    Log::send({LogColor::bgBlue("    Size: ") +
               LogColor::bgOrange(media->probeResult->format.size)});

    Log::send({LogColor::bgBlue("    Stream Count: ") +
               LogColor::bgOrange(
                   std::to_string(media->probeResult->format.nb_streams))});

    Log::send({LogColor::fgWhite(nl + "  " + ob + "Video Streams") + cb});

    // video streams
    for (int i = 0; i < media->probeResult->videoStreams.size(); i++) {
      ProbeResultStreamVideo prsv = media->probeResult->videoStreams[i];

      Log::send({"    " + ob + std::to_string(i) + cb + " " +
                 LogColor::fgOrange(prsv.codec_name)});

      Log::send(
          {LogColor::fgBlue("      Profile") + colon +
           LogColor::fgOrange(prsv.profile.empty() ? "None" : prsv.profile)});

      Log::send({LogColor::fgBlue("      Res") + colon +
                 LogColor::fgOrange(std::to_string(prsv.width) + "x" +
                                    std::to_string(prsv.height)) +
                 " (" + LogColor::fgOrange(prsv.display_aspect_ratio) + ")"});

      Log::send({LogColor::fgBlue("      Listed Duration") + colon +
                 LogColor::fgOrange(prsv.tags.DURATION.empty()
                                        ? "None"
                                        : prsv.tags.DURATION)});
    }

    Log::send({LogColor::fgWhite(nl + "  " + ob + "Audio Streams") + cb});

    // audio streams
    for (int i = 0; i < media->probeResult->audioStreams.size(); i++) {
      ProbeResultStreamAudio prsa = media->probeResult->audioStreams[i];

      Log::send({"    " + ob + std::to_string(i) + cb + " " +
                 LogColor::fgOrange(prsa.tags.language)});

      Log::send({LogColor::fgBlue("      Title") + colon +
                 LogColor::fgOrange(
                     prsa.tags.title.empty() ? "None" : prsa.tags.title)});

      Log::send({LogColor::fgBlue("      Codec") + colon +
                 LogColor::fgOrange(prsa.codec_name)});

      Log::send({LogColor::fgBlue("      Channels") + colon +
                 LogColor::fgOrange(std::to_string(prsa.channels))});

      Log::send({LogColor::fgBlue("      Channel Layout") + colon +
                 LogColor::fgOrange(prsa.channel_layout)});

      Log::send({LogColor::fgBlue("      Sample Rate") + colon +
                 LogColor::fgOrange(prsa.sample_rate)});

      Log::send({LogColor::fgBlue("      Bit Rate") + colon +
                 LogColor::fgOrange(prsa.tags.BPS)});
    }

    Log::send({LogColor::fgWhite(nl + "  " + ob + "Subtitle Streams") + cb});

    // subtitle streams
    for (int i = 0; i < media->probeResult->subtitleStreams.size(); i++) {
      ProbeResultStreamSubtitle prss = media->probeResult->subtitleStreams[i];

      Log::send({"    " + ob + std::to_string(i) + cb + " " +
                 LogColor::fgOrange(prss.tags.language)});

      Log::send({LogColor::fgBlue("      Title") + colon +
                 LogColor::fgOrange(prss.tags.title)});

      Log::send({LogColor::fgBlue("      Codec") + colon +
                 LogColor::fgOrange(prss.codec_name)});
    }

    t_queue.push(media);
  }

  runner->converting = t_queue;
}

void ChildDisplay::printJSON(void) {
  // clear console?
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
  // TODO: finish
  puts(Program::ticker->asJSON().dump().c_str());
}