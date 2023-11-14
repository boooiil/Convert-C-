#include "LogBuffer.h"

#include "Log.h"

LogBuffer::LogBuffer() : max(0), current(-1) {}
LogBuffer::LogBuffer(int max) : max(max), current(0) {}
LogBuffer::~LogBuffer() {}

void LogBuffer::addLine(std::string line) {
  Log::debug({"called addline, max:", std::to_string(max),
              "min:", std::to_string(current)});

  if (LogBuffer::current >= LogBuffer::max) {
    throw "Overflow.";
  }

  LogBuffer::line += line + "\n";
  LogBuffer::current++;
}

bool LogBuffer::isFull() { return LogBuffer::current >= LogBuffer::max; }

std::string LogBuffer::output() { return LogBuffer::line; }
