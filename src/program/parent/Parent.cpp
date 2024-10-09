#include "Parent.h"

#include <filesystem>
#include <nlohmann/json.hpp>
#include <queue>
#include <string>
#include <vector>

#include "../../utils/DirectoryUtils.h"
#include "../../utils/logging/Logger.h"
#include "./child/ChildProcess.h"

/**
 * Parent - Gather all files and queue into  ChildProcess.
 * Child process - Run convert and parse
 *   - Parse converting and pending
 *     - if not in map, add it
 *     - else, update non static fields
 *
 */

Parent::~Parent(void) {
  LOG_DEBUG("Deconstructing parent.");
  while (!this->pending.empty()) {
    ChildProcess* child = this->pending.front();
    this->pending.pop();

    LOG_DEBUG("Deleting child process in:", child->path);

    delete child;
  }
  while (!this->converting.empty()) {
    ChildProcess* child = this->converting.front();
    this->converting.pop();

    LOG_DEBUG("Deleting child process in:", child->path);

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
  LOG_DEBUG("Ending runner.");
  LOG_DEBUG("Expected to delete { }.");
}

void Parent::setEndable(bool flag) {
  LOG_DEBUG("Parent has been set as endable:",
            this->endable ? "True" : "False");
  this->endable = flag;
}

bool Parent::isEndable(void) { return this->endable; }

void Parent::fromJSON(nlohmann::json) {}

nlohmann::json Parent::toJSON(void) {
  nlohmann::json parent;
  nlohmann::json converting_json = nlohmann::json::array();
  nlohmann::json pending_json = nlohmann::json::array();

  // j["ChildProcesses"] = nlohmann::json::array();

  std::queue<ChildProcess*> t_queue;

  while (!this->pending.empty()) {
    ChildProcess* childProcess = this->pending.front();
    this->pending.pop();

    LOG("parent json: ", childProcess->path);

    converting_json.push_back(childProcess->toJSON());

    t_queue.push(childProcess);
  }

  this->pending = t_queue;

  t_queue = std::queue<ChildProcess*>();

  while (!this->converting.empty()) {
    ChildProcess* childProcess = this->converting.front();
    this->converting.pop();

    LOG("parent json: ", childProcess->path);

    pending_json.push_back(childProcess->toJSON());

    t_queue.push(childProcess);
  }

  this->converting = t_queue;

  parent["converting"] = converting_json;
  parent["pending"] = pending_json;

  return parent;
}
