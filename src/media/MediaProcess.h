#ifndef MEDIA_PROCESS
#define MEDIA_PROCESS

#include "../application/Container.h"
#include "../media/Media.h"

class MediaProcess {
 public:
  MediaProcess(Container&, Media&);
  ~MediaProcess();

  enum Status { WAIT, DONE, RUNNING, ERROR };

  virtual void start(std::string command);
  void setStatus(Status);
  virtual void parse(std::string);

  bool stop(void);
  bool isWaiting(void) const;
  bool isRunning(void) const;
  bool isError(void) const;
  bool isDone(void) const;

  Status getStatus(void) const;

 protected:
  Container& container;
  Media& media;
  Status status;
};

#endif  // !MEDIA_PROCESS
