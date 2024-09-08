#include "Parent.h"

#include <filesystem>
#include <nlohmann/json.hpp>
#include <queue>
#include <string>
#include <vector>

#include "../../logging/Log.h"
#include "../../utils/DirectoryUtils.h"
#include "./child/ChildProcess.h"

Parent::~Parent(void) {
  Log::debug({"[Parent.cpp] Deconstructing parent."});
  while (!this->pending.empty()) {
    ChildProcess* child = this->pending.front();
    this->pending.pop();

    Log::debug({"[Parent.cpp] Deleting child process in:", child->path});

    delete child;
  }
  while (!this->converting.empty()) {
    ChildProcess* child = this->converting.front();
    this->converting.pop();

    Log::debug({"[Parent.cpp] Deleting child process in:", child->path});

    delete child;
  }
}

void Parent::prepare(void) {
  std::vector<std::filesystem::directory_entry> files;

#ifdef _WIN32
  files = DirectoryUtils::findFileInSubdir({"convert.exe"});
#else
  files = DirectoryUtils::findFileInSubdir({"convert"});
#endif

  for (std::filesystem::directory_entry file : files) {
    std::string path = file.path().string();
    std::string filename = file.path().filename().string();

    ChildProcess* child = new ChildProcess(path, filename);
    child->getArgs();

    this->converting.push(child);
  };
}

void Parent::run(void) {}

void Parent::end(void) {
  Log::debug({"[Parent.cpp] Ending runner."});
  Log::debug({"[Program.cpp] Expected to delete { }."});
}

void Parent::setEndable(bool flag) {
  Log::debug(
      {"Parent has been set as endable:", this->endable ? "True" : "False"});
  this->endable = flag;
}

bool Parent::isEndable(void) { return this->endable; }

void Parent::fromJSON(nlohmann::json) {}

nlohmann::json Parent::asJSON(void) {
  nlohmann::json parent;
  nlohmann::json converting_json = nlohmann::json::array();
  nlohmann::json pending_json = nlohmann::json::array();

  // j["ChildProcesses"] = nlohmann::json::array();

  std::queue<ChildProcess*> t_queue;

  while (!this->pending.empty()) {
    ChildProcess* childProcess = this->pending.front();
    this->pending.pop();

    Log::send({"parent json: ", childProcess->path});

    converting_json.push_back(childProcess->asJSON());

    t_queue.push(childProcess);
  }

  this->pending = t_queue;

  t_queue = std::queue<ChildProcess*>();

  while (!this->converting.empty()) {
    ChildProcess* childProcess = this->converting.front();
    this->converting.pop();

    Log::send({"parent json: ", childProcess->path});

    pending_json.push_back(childProcess->asJSON());

    t_queue.push(childProcess);
  }

  this->converting = t_queue;

  parent["converting"] = converting_json;
  parent["pending"] = pending_json;

  return parent;
}
