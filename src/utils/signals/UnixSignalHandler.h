#ifdef __unix__ || __linux__
#ifndef UNIX_SIGNAL_HANDLER_H
#define UNIX_SIGNAL_HANDLER_H

class UnixSignalHandler {
 public:
  UnixSignalHandler();
  ~UnixSignalHandler();

  void registerHandler();
  void handleSignal(int signal);
};

#endif  // UNIX_SIGNAL_HANDLER_H
#endif
