#include "Log.h"

#include <initializer_list>
#include <iostream>
#include <string>

#include "../program/Program.h"
#include "../program/settings/enums/LoggingOptions.h"
#include "LogBuffer.h"
#include "LogColor.h"

LogBuffer* Log::buffer = nullptr;

void Log::init(void) { Log::debug({"[Log.cpp] Initializing log."}); }

void Log::send(std::initializer_list<std::string> messages) {
  std::string full_message = "";
  for (std::string message : messages) {
    full_message += message + " ";
  }
  std::cout << full_message << std::endl;
}

// void Log::sendBuffer(int length, std::string message) {
//   if (Log::buffer == nullptr) {
//     Log::debug({"[Log.cpp] buffer is null"});
//     Log::buffer = new LogBuffer(length);
//   }
//
//   Log::debug({"[Log.cpp] called sendbuffer, len " + length});
//
//   Log::buffer->addLine(message);
//
//   if (Log::buffer->isFull()) {
//     Log::send({Log::buffer->output()});
//     delete Log::buffer;
//   }
// }

// void Log::sendBuffer(int length, const char* message) {
//   if (Log::buffer == nullptr) {
//     Log::buffer = new LogBuffer(length);
//   }
//
//   Log::debug({"[Log.cpp] called sendbuffer, len " + std::to_string(length)});
//
//   Log::buffer->addLine(std::string(message));
//
//   if (Log::buffer->isFull()) {
//     Log::debug({"[Log.cpp] buffer is full"});
//
//     Log::send({Log::buffer->output()});
//     delete Log::buffer;
//   }
// }

void Log::debug(std::initializer_list<std::string> messages) {
  if (Program::settings == nullptr) {
    std::cout << "-!-!-!-!- Program settings is null -!-!-!-!-" << std::endl;
    Log::send(messages);
    std::cout << "-!-!-!-!- Program settings is null -!-!-!-!-" << std::endl;
    return;
  }

  if (Program::settings->argumentParser == nullptr) {
    std::cout << "-!-!-!-!- Argument parser is null -!-!-!-!-" << std::endl;
    Log::send(messages);
    std::cout << "-!-!-!-!- Argument parser is null -!-!-!-!-" << std::endl;
    return;
  }

  if (LoggingOptions::isDebug(Program::settings->argumentParser->loggingFormat))
    Log::send(messages);
}

void Log::sendPlain(std::initializer_list<std::string> messages) {
  std::string full_message = "";
  for (std::string message : messages) {
    full_message += message + " ";
  }
  std::cout << full_message << std::endl;
}

void Log::flushBuffer() {
  Log::debug({"[Log.cpp] called flush buffer"});
  if (Log::buffer == nullptr)
    Log::debug({"[Log.cpp] buffer is empty"});
  else
    Log::send({LogColor::fgRed(Log::buffer->output())});
  delete Log::buffer;
}

void Log::end(void) {
  Log::debug({"[Log.cpp] Ending log."});
  if (Log::buffer != nullptr) delete Log::buffer;
};

bool Log::hasBuffer() { return true; }