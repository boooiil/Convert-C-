#ifndef CHILD_PROCESS_H
#define CHILD_PROCESS_H

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

#include "../../child/media/Media.h"
#include "../../generics/JSONSerializableRunner.h"
#include "../../settings/enums/Activity.h"

class ChildProcess : public JSONSerializableRunner {
 public:
  ChildProcess(std::string path, std::string filename);
  ~ChildProcess(void);

  int pid;
  long started;
  long ended;

  std::vector<Media*> converting;
  std::vector<Media*> pending;

  std::string path;
  std::string filename;
  std::string args;

  void getArgs(void);

  void doConversion(void);

  /**
   * @brief Get the activity type.
   *
   * @return Activity::ActivityType - Activity type.
   */
  Activity::ActivityType getActivity(void);

  /**
   * @brief Check if the current media is processing.
   *
   * @return true if the media activity is STATISTICS, CONVERT or VALIDATE.
   * @return false if the media activity is WAITING-like, FINISHED, or
   * FAILED-like.
   */
  const bool isProcessing(void);

  /**
   * @brief Check if the current media has failed processing.
   *
   * @return true if the media activity is FAILED-like.
   */
  const bool hasFailed(void);

  /**
   * @brief Check if the current media has failed processing.
   *
   * @return true if the media activity is FINISHED.
   */
  const bool hasFinished(void);

  /**
   * @brief Check if the current media is waiting to be processed.
   *
   * @return true if the media activity is WAITING.
   */
  const bool isWaiting(void);

  /**
   * @brief Check if the current media is waiting to convert.
   *
   * @return true if the media activity is WAITING_CONVERT.
   */
  const bool isWaitingToConvert(void);

  void fromJSON(nlohmann::json childProcess);

  /**
   * @brief Returns the process as a JSON object.
   *
   * @return nlohmann::json
   */
  nlohmann::json asJSON(void);

  // Inherited via GenericRunner
  void prepare(void) override;
  void run(void) override;
  void end(void) override;
  void setEndable(bool flag) override;
  bool isEndable(void) override;

 private:
  Activity::ActivityType activity;
  bool endable;
};

#endif  // !CHILD_PROCESS_H
