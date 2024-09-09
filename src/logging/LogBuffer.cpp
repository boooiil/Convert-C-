#include "LogBuffer.h"

#include <string>

#include "Log.h"

LogBuffer::LogBuffer(int max) : max(max), current(0) {}

void LogBuffer::addLine(std::string provided_line) {
  Log::debug({"[LogBuffer.cpp] called addline, max:", std::to_string(max),
              "min:", std::to_string(current)});

  if (this->current >= this->max) {
    delete this;
    throw "Overflow.";
  }

  try {
    this->line += (provided_line + "\n");
  } catch (const std::exception& e) {
    throw e.what();
  }
  LogBuffer::current++;
}

bool LogBuffer::isFull() { return this->current >= this->max; }

std::string LogBuffer::output() { return this->line; }
