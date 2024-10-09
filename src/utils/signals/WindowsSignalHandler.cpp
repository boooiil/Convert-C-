#ifdef _WIN32
#include "WindowsSignalHandler.h"

#include <Windows.h>
#include <consoleapi.h>

#include "../../program/Program.h"
#include "../../utils/logging/Logger.h"

WindowsSignalHandler::WindowsSignalHandler() {}
WindowsSignalHandler::~WindowsSignalHandler() {}

void WindowsSignalHandler::registerHandler() {
  /*LOG("Registering signal handler.");
  if (!SetConsoleCtrlHandler(WindowsSignalHandler::winHandle, TRUE)) {
    LOG("Failed to register signal handler.");
  }
  LOG("Signal handler registered.");*/
}

BOOL WINAPI WindowsSignalHandler::winHandle(DWORD signal) {
  LOG("Signal received.");
  switch (signal) {
    case CTRL_BREAK_EVENT:
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
      LOG("Interrupt signal received.");
      Program::stopFlag = true;
      return true;
    default:
      return false;
  }
}
#endif