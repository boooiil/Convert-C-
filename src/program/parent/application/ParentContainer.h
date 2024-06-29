#ifndef PARENT_CONTAINER_H
#define PARENT_CONTAINER_H

#include <queue>

#include "../../application/arguments/UserArguments.h"
#include "../../application/settings/ProgramSettings.h"
#include "../../child/ChildConversionProcess.h"
#include "../../logging/Log.h"

class ParentContainer {
 public:
  ParentContainer();
  ~ParentContainer();

  Log log;

  UserArguments userArguments;
  UserSettings userSettings;        // this cannot be the same
  ProgramSettings programSettings;  // this cannot be the same

  /// @brief Holds current child conversion file(s) being converted.
  std::queue<ChildConversionProcess*> converting;
  /// @brief Holds child conversion files that are waiting to be converted.
  std::queue<ChildConversionProcess*> pending;

  /**
   * @brief Scans working directory for convert files and adds them to pending
   * queue.
   *
   */
  void scanWorkingDir(void);

  // nlohmann::json asJSON();
};

#endif  // PARENT_CONTAINER_H
