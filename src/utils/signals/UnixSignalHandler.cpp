#if defined(__unix__) || defined(__linux__)

#include "UnixSignalHandler.h"

#include <signal.h>

#include <iostream>

#include "../../logging/Log.h"
#include "../../program/Program.h"

UnixSignalHandler::UnixSignalHandler() {}
UnixSignalHandler::~UnixSignalHandler() {}

void UnixSignalHandler::registerHandler() {
  Log::send({"[UNIXSignalHandler.cpp] Registering signal handler."});
  signal(SIGKILL, handleSignal);
  signal(SIGTERM, handleSignal);
  signal(SIGINT, handleSignal);
  signal(SIGQUIT, handleSignal);
  Log::send({"[UNIXSignalHandler.cpp] Signal handler registered."});
}

void UnixSignalHandler::handleSignal(int signal) {
  std::cout << "Interrupt signal (" << signal << ") recieved." << std::endl;
  Program::stopFlag = true;
}
#endif