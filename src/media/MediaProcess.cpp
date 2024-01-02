#include "MediaProcess.h"

#include <array>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#ifdef _WIN32
#include <cstdio>
#define popen _popen
#define pclose _pclose
#else
#include <cstdio>
#endif

/* TODO: I don't really need to pass container and media to this class */

MediaProcess::MediaProcess(Container& container, Media& media)
    : container(container),
      media(media),
      status(MediaProcess::Status::WAIT),
      stop_req(false) {}

MediaProcess::~MediaProcess() {
  MediaProcess::container.log.debug({"[MediaProcess.cpp] DESTRUCTOR CALLED"});
}

/**
 * @brief Start the process.
 *
 * @param command The command to execute.
 */
void MediaProcess::start(std::string command) {
  command += " 2>&1";
  MediaProcess::container.log.debug(
      {"[MediaProcess.cpp] SENDING COMMAND:", command});

  MediaProcess::status = MediaProcess::Status::RUNNING;

  std::array<char, 128> buffer;
  std::string result;
  int ch;

  // Open pipe to file
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  if (stop_req) {
    MediaProcess::container.log.debug(
        {"Stop request received before starting the loop"});
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
      MediaProcess::container.log.debug(
          {"Stop request received during the loop"});
      break;
    }
  }
}

/**
 * @brief Set the status of the process.
 *
 * @param status The status to set.
 */
void MediaProcess::setStatus(MediaProcess::Status status) {
  MediaProcess::status = status;
}

/**
 * @brief Parse the data from the process.
 *
 * @param data The data to parse.
 */
void MediaProcess::parse(std::string data) {
  container.log.debug({"WARNING, USING DEFAULT PARSER", data});
}

/**
 * @brief Stop the process.
 *
 * @return true Process was stopped.
 * @return false Process was not stopped.
 */
void MediaProcess::stop(void) { stop_req = true; }

/**
 * @brief Check if the process is waiting.
 *
 * @return true Process is waiting.
 * @return false Process is not waiting.
 */
bool MediaProcess::isWaiting(void) const {
  return MediaProcess::status == MediaProcess::Status::WAIT;
}

/**
 * @brief Check if the process is running.
 *
 * @return true Process is running.
 * @return false Process is not running.
 */
bool MediaProcess::isRunning(void) const {
  return MediaProcess::status == MediaProcess::Status::RUNNING;
}

/**
 * @brief Check if the process is in an error state.
 *
 * @return true Process is in an error state.
 * @return false Process is not in an error state.
 */
bool MediaProcess::isError(void) const {
  return MediaProcess::status == MediaProcess::Status::_ERROR;
}

/**
 * @brief Check if the process is done.
 *
 * @return true Process is done.
 * @return false Process is not done.
 */
bool MediaProcess::isDone(void) const {
  return MediaProcess::status == MediaProcess::Status::DONE;
}

/**
 * @brief Get the status of the process.
 *
 * @return ExecuteProcess::Status The status of the process.
 */
MediaProcess::Status MediaProcess::getStatus(void) const {
  return MediaProcess::status;
}