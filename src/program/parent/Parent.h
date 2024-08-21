#ifndef PARENT_H
#define PARENT_H

#include <nlohmann/json_fwd.hpp>
#include <queue>

#include "../generics/JSONSerializableRunner.h"
#include "child/ChildProcess.h"
#include "ticker/ParentTicker.h"

class Parent : public JSONSerializableRunner {
 public:
  ~Parent(void);

  /// @brief Current converting child processes.
  std::queue<ChildProcess*> converting;
  /// @brief Pending child processes.
  std::queue<ChildProcess*> pending;

  /// @brief Run preparation tasks for parent.
  void prepare(void);
  ///  @brief Run parent process.
  void run(void);
  ///  @brief End parent process.
  void end(void);

  /**
   * @brief Returns the JSON representation of this object.
   *
   * @return nlohmann::json
   */
  nlohmann::json asJSON(void);

 private:
};

#endif  // !PARENT_H