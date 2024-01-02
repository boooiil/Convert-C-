#ifndef MEDIA_PROCESS
#define MEDIA_PROCESS

#include "../application/Container.h"
#include "../media/Media.h"

class MediaProcess {
 public:
  MediaProcess(Container&, Media&);
  ~MediaProcess();

  enum Status { WAIT, DONE, RUNNING, _ERROR };

  virtual void start(std::string command);
  virtual void parse(std::string);

  void setStatus(Status);
  void stop(void);

  bool isWaiting(void) const;
  bool isRunning(void) const;
  bool isError(void) const;
  bool isDone(void) const;

  Status getStatus(void) const;

 protected:
  Container& container;
  Media& media;
  Status status;

 private:
  bool stop_req;
};

#endif  // !MEDIA_PROCESS
