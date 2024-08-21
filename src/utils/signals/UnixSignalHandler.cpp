#ifdef __unix__ || __linux__

#include "UnixSignalHandler.h"

#include <iostream>

#include "../../logging/Log.h"
#include "../../program/Program.h"

UnixSignalHandler::UnixSignalHandler() {}
UnixSignalHandler::~UnixSignalHandler() {}

void UnixSignalHandler::registerHandler() {
  Log::send({"[WindowsSignalHandler.cpp] Registering signal handler."});
  signal(SIGKILL, handleSignal);
  signal(SIGTERM, handleSignal);
  signal(SIGINT, handleSignal);
  signal(SIGQUIT, handleSignal);
  Log::send({"[WindowsSignalHandler.cpp] Signal handler registered."});
}

void UnixSignalHandler::handleSignal(int signal) {
  std::cout << "Interrupt signal (" << signal << ") recieved." << std::endl;
  Program::end();
}
#endif