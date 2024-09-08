#include "ChildDisplay.h"

#include <queue>
#include <string>

#include "../../../logging/Log.h"
#include "../../../logging/LogColor.h"
#include "../../Program.h"
#include "../../generics/GenericRunner.h"
#include "../../ticker/NTicker.h"
#include "../Child.h"
#include "../ffmpeg/ProbeResultStreamAudio.h"
#include "../ffmpeg/ProbeResultStreamSubtitle.h"
#include "../ffmpeg/ProbeResultStreamVideo.h"
#include "../media/Media.h"

void ChildDisplay::print(void) {
  // TODO: finish
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
  // TODO: finish
}