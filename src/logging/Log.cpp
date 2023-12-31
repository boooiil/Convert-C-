#include "Log.h"

#include <iostream>

#include "../application/Debug.h"

Log::Log() : buffer(nullptr) {}
Log::~Log() {
  Log::send({"deconstructing buffer"});
  delete this->buffer;
}

void Log::send(std::initializer_list<std::string> messages) {
  std::string full_message = "";
  for (std::string message : messages) {
    full_message += message + " ";
  }
  std::cout << full_message << std::endl;
}

void Log::sendBuffer(int length, std::string message) {
  if (Log::buffer == nullptr) {
    Log::buffer = new LogBuffer(length);
  }

  Log::debug({"[Log.cpp] called sendbuffer, len " + length});

  Log::buffer->addLine(message);

  if (Log::buffer->isFull()) {
    Log::send({Log::buffer->output()});
    Log::buffer = nullptr;
  }
}

void Log::sendBuffer(int length, const char* message) {
  if (Log::buffer == nullptr) {
    Log::buffer = new LogBuffer(length);
  }

  Log::debug({"[Log.cpp] called sendbuffer, len " + std::to_string(length)});

  Log::buffer->addLine(std::string(message));

  if (Log::buffer->isFull()) {
    Log::debug({"[Log.cpp] buffer is full"});

    Log::send({Log::buffer->output()});
    Log::buffer = nullptr;
  }
}

void Log::debug(std::initializer_list<std::string> messages) {
  if (Debug::toggle) Log::send(messages);
}

void Log::sendPlain(std::initializer_list<std::string> messages) {
  std::string full_message = "";
  for (std::string message : messages) {
    full_message += message + " ";
  }
  std::cout << full_message << std::endl;
}

void Log::flushBuffer() {
  Log::debug({"called flush buffer"});
  if (Log::buffer == nullptr)
    Log::send({"buffer is empty"});
  else
    Log::send({LogColor::fgRed(Log::buffer->output())});
  Log::buffer = nullptr;
}

bool Log::hasBuffer() { return true; }