/*********************************************************************
 * @file   MediaProcess.h
 * @brief  Media Process class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef MEDIA_PROCESS
#define MEDIA_PROCESS

#include <string>

#include "../media/Media.h"

/**
 * @brief Handle execution of commands on the system and track their status.
 */
class MediaProcess {
 public:
  /**
   * @brief Construct a new Media Process object.
   */
  MediaProcess(Media* media);
  ~MediaProcess(void);

  /**
   * @brief Status of the process.
   */
  enum Status { WAIT, DONE, RUNNING, _ERROR };

  /**
   * @brief Start the process.
   *
   * @param[in] command - Command to be executed.
   */
  virtual void start(std::string command);

  /**
   * @brief Parse the data from the process.
   *
   * @param[in] data - Data to be parsed.
   */
  virtual void parse(std::string data);

  /**
   * @brief Set the status of the process.
   *
   * @param[in]  - Status to be set.
   */
  void setStatus(Status);

  /**
   * @brief Stop the process.
   *
   */
  void stop(void);

  /**
   * @brief Check if the process is waiting.
   *
   * @return true  - Process is waiting.
   * @return false - Process is not waiting.
   */
  bool isWaiting(void) const;

  /**
   * @brief Check if the process is running.
   *
   * @return true  - Process is running.
   * @return false - Process is not running.
   */
  bool isRunning(void) const;

  /**
   * @brief Check if the process is in error.
   *
   * @return true  - Process is in error.
   * @return false - Process is not in error.
   */
  bool isError(void) const;

  /**
   * @brief Check if the process is done.
   *
   * @return true  - Process is done.
   * @return false - Process is not done.
   */
  bool isDone(void) const;

  /**
   * @brief Get the status of the process.
   *
   * @return Status - Status of the process.
   */
  Status getStatus(void) const;

 protected:
  Media* media;
  Status status;  /// @brief Status of the process.

 private:
  bool stop_req;  /// @brief Stop request.
};

#endif  // !MEDIA_PROCESS
