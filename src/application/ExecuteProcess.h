#ifndef EXECUTE_PROCESS
#define EXECUTE_PROCESS

#include <string>

class ExecuteProcess {
 public:
  ExecuteProcess();
  ~ExecuteProcess();

  enum Status { WAIT, DONE, RUNNING, ERROR };

  void start(std::string command);
  void setStatus(Status);

  bool stop(void);
  bool isWaiting(void) const;
  bool isRunning(void) const;
  bool isError(void) const;
  bool isDone(void) const;

  Status getStatus(void) const;

 private:
  Status status;
};

#endif  //! EXECUTE_PROCESS
