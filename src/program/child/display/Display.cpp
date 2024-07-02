#include "./Display.h"

#include <math.h>

#include "../utils/NumberUtils.h"
#include "../utils/StringUtils.h"
#include "../utils/TimeUtils.h"

Display::Display(Container* container) : container(container) {}

Display::~Display() { Log::debug({"[Display.cpp] deconstructing Display"}); }

void Display::print() {
  int bufferLen = static_cast<int>(this->container->converting.size()) +
                  static_cast<int>(this->container->pending.size()) + 1;

  std::string ob = LogColor::fgGray("[");
  std::string cb = LogColor::fgGray("]");

  std::string time = ob + LogColor::fgCyan("TIME") + cb + " " +
                     TimeUtils::dateFormat(TimeUtils::getEpoch());
  std::string encoder = ob + LogColor::fgCyan("TARGET ENC") + cb + " " +
                        LogColor::fgGray(Encoders::getValue(
                            this->container->userSettings.wantedEncoder));
  std::string runningEncoder =
      ob + LogColor::fgCyan("ENC") + cb + " " +
      LogColor::fgGray(
          Encoders::getValue(this->container->programSettings.runningEncoder));
  std::string runningDecoder =
      ob + LogColor::fgCyan("ACC") + cb + " " +
      LogColor::fgGray(HWAccelerators::getValue(
          this->container->programSettings.runningHWAccel));
  std::string resolution =
      ob + LogColor::fgCyan("RES") + cb + " " +
      LogColor::fgGray(this->container->userSettings.quality.get().name);
  std::string tune =
      ob + LogColor::fgCyan("TUNE") + cb + " " +
      LogColor::fgGray(Tunes::getValue(this->container->userSettings.tune));
  std::string amount =
      ob + LogColor::fgCyan("AMOUNT") + cb + " " +
      LogColor::fgGray(std::to_string(container->userSettings.amount));

  std::string constrain = ob + LogColor::fgRed("CONSTRAIN") + cb;
  std::string debug = ob + LogColor::fgRed("DEBUG") + cb;
  std::string crop = ob + LogColor::fgRed("CROP") + cb;

  std::string header = time + " " + encoder + " " + runningEncoder + " " +
                       runningDecoder + " " + resolution + " " + tune + " " +
                       amount;

  if (this->container->userSettings.useConstrain) {
    header += " " + constrain;
  }

  if (this->container->userSettings.loggingFormat == LoggingOptions::DEBUG) {
    header += " " + debug;
  }

  if (this->container->userSettings.crop) {
    header += " " + crop;
  }

// clear console?
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
  this->container->log.sendBuffer(bufferLen, header);

  std::queue<Media*> t_queue;

  while (!this->container->converting.empty()) {
    Media* media = this->container->converting.front();
    this->container->converting.pop();

    float mediaFPS = media->working->fps > 0 ? media->working->fps : 1;
    int totalFrames = media->video->totalFrames;
    long completedFrames = static_cast<long>(media->working->completedFrames);
    int diff = static_cast<int>(
        ceil((totalFrames - completedFrames) / mediaFPS) * 1000);

    // create a time util to get this
    std::string started = ob + LogColor::fgCyan("START") + cb + " " +
                          TimeUtils::timeFormat(media->started);
    // create a time util to get this
    std::string eta = ob + LogColor::fgCyan("ETA") + cb + " " +
                      TimeUtils::durationFormat(diff);

    float crf = media->working->quality;
    int v_crf = media->video->crf;

    float workingFPS = media->working->fps;
    float videoFPS = media->video->fps;

    std::string fileName = ob + LogColor::fgCyan("FILE") + cb + " " +
                           LogColor::fgGray(StringUtils::truncateString(
                               media->file->modifiedFileName, 25));

    std::string activity = ob + LogColor::fgCyan("ACT") + cb + " " +
                           Activity::getValue(media->getActivity());

    std::string percent =
        ob + LogColor::fgCyan("PROG") + cb + " " +
        std::to_string(
            (int)(((float)completedFrames / (float)totalFrames) * 100)) +
        "%";

    std::string cq = ob + LogColor::fgCyan("QUAL") + cb + " " +
                     NumberUtils::formatNumber((v_crf / crf) * 100, 2) + "%";
    std::string speed = ob + LogColor::fgCyan("SPEED") + cb + " " +
                        NumberUtils::formatNumber(workingFPS / videoFPS, 2);

    std::string bitrate =
        ob + LogColor::fgCyan("BITRATE") + cb + " " +
        NumberUtils::formatNumber(media->working->bitrate, 2) + "kb/s";

    this->container->log.sendBuffer(
        bufferLen, fileName + " " + activity + " " + started + " " + percent +
                       " " + cq + " " + bitrate + " " + speed + " " + eta);

    t_queue.push(media);
  }

  this->container->converting = t_queue;
  t_queue = std::queue<Media*>();

  while (!this->container->pending.empty()) {
    Media* media = this->container->pending.front();
    this->container->pending.pop();

    std::string fileName = ob + LogColor::fgCyan("FILE") + cb + " " +
                           LogColor::fgGray(StringUtils::truncateString(
                               media->file->modifiedFileName, 25));

    std::string activity = ob + LogColor::fgCyan("ACT") + cb + " " +
                           Activity::getValue(media->getActivity());

    if (media->hasFinished()) {
      int calculatedSize = static_cast<int>(floor(
          ((media->file->size - media->file->newSize) / media->file->size) *
          100));

      std::string ended = ob + LogColor::fgCyan("END") + cb + " " +
                          TimeUtils::timeFormat(media->ended);
      std::string elapsed =
          ob + LogColor::fgCyan("ELAPSED") + cb + " " +
          TimeUtils::durationFormat((media->ended - media->started) * 1000);

      std::string reduced = ob + LogColor::fgCyan("REDUCED") + cb + " " +
                            std::to_string(calculatedSize) + "%";

      this->container->log.sendBuffer(bufferLen, fileName + " " + activity +
                                                     " " + reduced + " " +
                                                     ended + " " + elapsed);
    } else {
      this->container->log.sendBuffer(bufferLen, fileName + " " + activity);
    }

    t_queue.push(media);
  }
  this->container->pending = t_queue;
}
void Display::printDebug() {}
void Display::printJSON() {
// clear console?
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif

  using namespace nlohmann;
  json export_json;

  // CONTAINER["settings"] = json::object();
  export_json["converting"] = json::array();
  export_json["pending"] = json::array();

  std::queue<Media*> t_queue;

  while (!container->converting.empty()) {
    Media* internal_media = container->converting.front();

    json media;
    json mediaFile;
    json mediaVideo;
    json mediaWorking;

    media["activity"] = Activity::getValue(internal_media->getActivity());
    media["started"] = internal_media->started;
    media["ended"] = internal_media->ended;

    mediaFile["modifiedFileName"] = internal_media->file->modifiedFileName;
    mediaFile["ext"] = internal_media->file->ext;
    mediaFile["size"] = internal_media->file->size;
    mediaFile["newSize"] = internal_media->file->newSize;
    mediaFile["validationSize"] = internal_media->file->validationSize;

    mediaVideo["fps"] = internal_media->video->fps;
    mediaVideo["totalFrames"] = internal_media->video->totalFrames;

    mediaWorking["fps"] = internal_media->working->fps;
    mediaWorking["completedFrames"] = internal_media->working->completedFrames;
    mediaWorking["quality"] = internal_media->working->quality;
    mediaWorking["bitrate"] = internal_media->working->bitrate;

    media["file"] = mediaFile;
    media["video"] = mediaVideo;
    media["working"] = mediaWorking;

    export_json["converting"].push_back(media);

    container->converting.pop();
    t_queue.push(internal_media);
  }

  container->converting = t_queue;
  t_queue = std::queue<Media*>();

  while (!container->pending.empty()) {
    Media* internal_media = container->pending.front();

    json media;
    json mediaFile;
    json mediaVideo;
    json mediaWorking;

    media["activity"] = Activity::getValue(internal_media->getActivity());
    media["started"] = internal_media->started;
    media["ended"] = internal_media->ended;

    mediaFile["modifiedFileName"] = internal_media->file->modifiedFileName;
    mediaFile["ext"] = internal_media->file->ext;
    mediaFile["size"] = internal_media->file->size;
    mediaFile["newSize"] = internal_media->file->newSize;
    mediaFile["validationSize"] = internal_media->file->validationSize;

    mediaVideo["fps"] = internal_media->video->fps;
    mediaVideo["totalFrames"] = internal_media->video->totalFrames;

    mediaWorking["fps"] = internal_media->working->fps;
    mediaWorking["completedFrames"] = internal_media->working->completedFrames;
    mediaWorking["quality"] = internal_media->working->quality;
    mediaWorking["bitrate"] = internal_media->working->bitrate;

    media["file"] = mediaFile;
    media["video"] = mediaVideo;
    media["working"] = mediaWorking;

    media["file"] = mediaFile;
    media["video"] = mediaVideo;
    media["working"] = mediaWorking;

    export_json["pending"].push_back(media);

    container->pending.pop();
    t_queue.push(internal_media);
  }

  container->pending = t_queue;

  puts(export_json.dump().c_str());
}
