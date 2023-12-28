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
  MediaProcess::container.log.debug(
      {"[MediaProcess.cpp] SENDING COMMAND:", command});

  MediaProcess::status = MediaProcess::Status::RUNNING;

  std::array<char, 128> buffer;
  std::string result;

  // Open pipe to file
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  // Read from pipe
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr &&
         !stop_req) {
    MediaProcess::container.log.debug({"RAW OUTPUT: ", buffer.data()});
    result += buffer.data();

    // parse the data using overriden func
    parse(buffer.data());

    // std::this_thread::sleep_for(
    //     std::chrono::seconds(1));  // delay for long running processes
  }

  MediaProcess::container.log.debug({"[MediaProcess.cpp] OUTPUT: ", result});
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
void MediaProcess::parse(std::string data) { return; }

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
  return MediaProcess::status == MediaProcess::Status::ERROR;
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