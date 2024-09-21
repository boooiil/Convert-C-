#include "ChildProcess.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "../../../logging/Log.h"
#include "../../child/media/Media.h"
#include "../../settings/enums/Activity.h"
#include "ChildProcessConversion.h"

ChildProcess::ChildProcess(std::string path, std::string filename)
    : path(path),
      filename(filename),
      pid(-1),
      endable(true),
      ended(0),
      started(0),
      activity(Activity::WAITING) {}

ChildProcess::~ChildProcess(void) {}

Activity::ActivityType ChildProcess::getActivity() { return this->activity; }

void ChildProcess::getArgs(void) {
  std::cout << this->path << " arguments: ";
  std::getline(std::cin, this->args);

  this->args = "-lf json " + this->args;
}

const bool ChildProcess::isProcessing() {
  switch (this->activity) {
    case Activity::STATISTICS:
    case Activity::CONVERT:
    case Activity::VALIDATE:
      return true;
    default:
      return false;
  }
}

const bool ChildProcess::hasFailed() {
  switch (this->activity) {
    case Activity::FAILED:
    case Activity::FAILED_CODEC:
    case Activity::FAILED_CONTAINER:
    case Activity::FAILED_CORRUPT:
    case Activity::FAILED_FILE:
    case Activity::FAILED_FILE_MISSING:
    case Activity::FAILED_FILE_NOT_RECOGNIZED:
    case Activity::FAILED_FILE_PERMISSIONS:
    case Activity::FAILED_HARDWARE:
    case Activity::FAILED_INVALID_AUDIO_STREAMS:
    case Activity::FAILED_JSON_PARSE:
    case Activity::FAILED_SYSTEM:
      return true;
    default:
      return false;
  }
}

const bool ChildProcess::hasFinished() {
  return this->activity == Activity::FINISHED;
}

const bool ChildProcess::isWaiting() {
  return this->activity == Activity::WAITING;
}

const bool ChildProcess::isWaitingToConvert() {
  return this->activity == Activity::WAITING_CONVERT;
}

void ChildProcess::prepare(void) {}

void ChildProcess::run(void) {}

void ChildProcess::doConversion(void) {
  this->activity = Activity::CONVERT;

  Log::debug({"[ChildProcess.cpp] Running conversion for:", this->path});

  ChildProcessConversion conversion(this);
  conversion.start(this->path + "/" + this->filename + " " + this->args);
}

void ChildProcess::end(void) {}

void ChildProcess::setEndable(bool flag) { this->endable = flag; }

bool ChildProcess::isEndable(void) { return this->endable; }

void ChildProcess::fromJSON(nlohmann::json childProcess) {
  nlohmann::json runner = childProcess["Runner"];

  for (nlohmann::json mediaFile : runner["converting"]) {
    Media* media = new Media();
    media->fromJSON(mediaFile);
    this->converting.push_back(media);
  }

  for (nlohmann::json mediaFile : runner["pending"]) {
    Media* media = new Media();
    media->fromJSON(mediaFile);
    this->pending.push_back(media);
  }
}

nlohmann::json ChildProcess::asJSON(void) {
  nlohmann::json childProcess;

  childProcess["path"] = this->path;
  childProcess["filename"] = this->filename;
  childProcess["args"] = this->args;

  return childProcess;
}
