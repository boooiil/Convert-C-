#include "MediaProcess.h"

#include <array>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "../logging/Log.h"

#ifdef _WIN32
#include <cstdio>
#define popen _popen
#define pclose _pclose
#else
#include <cstdio>
#endif

/* TODO: I don't really need to pass container and media to this class */

MediaProcess::MediaProcess(Container* container, Media* media)
    : container(container),
      media(media),
      status(MediaProcess::Status::WAIT),
      stop_req(false) {}

MediaProcess::~MediaProcess() {
  Log::debug({"[MediaProcess.cpp] DESTRUCTOR CALLED"});
}

void MediaProcess::start(std::string command) {
  command += " 2>&1";
  Log::debug({"[MediaProcess.cpp] SENDING COMMAND:", command});

  MediaProcess::status = MediaProcess::Status::RUNNING;

  std::string result;
  int ch;

  // Open pipe to file
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  if (stop_req) {
    Log::debug({"Stop request received before starting the loop"});
    return;
  }

  // Read from pipe
  while ((ch = fgetc(pipe.get())) != EOF && !stop_req) {
    result += static_cast<char>(ch);

    // If the last character is a newline, parse the result
    if (ch == 10 || ch == 13) {
      // parse the data using overriden func
      parse(result);
      result.clear();  // Clear the result for the next line
    }

    if (stop_req) {
      Log::debug({"Stop request received during the loop"});
      break;
    }
  }
}

void MediaProcess::setStatus(MediaProcess::Status provided_status) {
  MediaProcess::status = provided_status;
}

void MediaProcess::parse(std::string data) {
  Log::debug({"WARNING, USING DEFAULT PARSER", data});
}

void MediaProcess::stop(void) { stop_req = true; }

bool MediaProcess::isWaiting(void) const {
  return MediaProcess::status == MediaProcess::Status::WAIT;
}

bool MediaProcess::isRunning(void) const {
  return MediaProcess::status == MediaProcess::Status::RUNNING;
}

bool MediaProcess::isError(void) const {
  return MediaProcess::status == MediaProcess::Status::_ERROR;
}

bool MediaProcess::isDone(void) const {
  return MediaProcess::status == MediaProcess::Status::DONE;
}

MediaProcess::Status MediaProcess::getStatus(void) const {
  return MediaProcess::status;
}