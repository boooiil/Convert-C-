#include "ChildProcess.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

ChildProcess::ChildProcess(std::string path, std::string filename)
    : path(path), filename(filename), pid(-1) {}

ChildProcess::~ChildProcess(void) {}

void ChildProcess::start(void) {}

void ChildProcess::getArgs(void) {
  std::cout << this->path << " arguments: ";
  std::getline(std::cin, this->args);

  this->args = "-lf JSON " + this->args;
}

nlohmann::json ChildProcess::asJSON(void) {
  nlohmann::json childProcess;

  childProcess["path"] = this->path;
  childProcess["filename"] = this->filename;
  childProcess["args"] = this->args;

  return childProcess;
}
