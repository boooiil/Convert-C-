#ifndef CHILD_PROCESS_H
#define CHILD_PROCESS_H

#include <nlohmann/json_fwd.hpp>
#include <string>

class ChildProcess {
 public:
  ChildProcess(std::string path, std::string filename);
  ~ChildProcess(void);

  int pid;

  std::string path;
  std::string filename;
  std::string args;

  void start(void);
  void getArgs(void);

  /**
   * @brief Returns the process as a JSON object.
   *
   * @return nlohmann::json
   */
  nlohmann::json asJSON(void);
};

#endif  // !CHILD_PROCESS_H
