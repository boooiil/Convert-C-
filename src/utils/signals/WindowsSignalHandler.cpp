#ifdef _WIN32
#include "./WindowsSignalHandler.h"

#include <Windows.h>
#include <consoleapi.h>

#include "../../logging/Log.h"
#include "../../program/Program.h"

WindowsSignalHandler::WindowsSignalHandler() {}
WindowsSignalHandler::~WindowsSignalHandler() {}

void WindowsSignalHandler::registerHandler() {
  /*Log::send({"[WindowsSignalHandler.cpp] Registering signal handler."});
  if (!SetConsoleCtrlHandler(WindowsSignalHandler::winHandle, TRUE)) {
    Log::send(
        {"[WindowsSignalHandler.cpp] Failed to register signal handler."});
  }
  Log::send({"[WindowsSignalHandler.cpp] Signal handler registered."});*/
}

BOOL WINAPI WindowsSignalHandler::winHandle(DWORD signal) {
  Log::send({"[WindowsSignalHandler.cpp] Signal received."});
  switch (signal) {
    case CTRL_BREAK_EVENT:
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
      Log::send({"[WindowsSignalHandler.cpp] Interrupt signal received."});
      Program::stopFlag = true;
      return true;
    default:
      return false;
  }
}
#endif