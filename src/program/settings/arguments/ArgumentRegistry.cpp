#include "ArgumentRegistry.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "GenericArgument.h"

std::unordered_map<std::string, std::shared_ptr<GenericArgument>>
    ArgumentRegistry::arguments = {};

void ArgumentRegistry::add(std::string flag,
                           std::shared_ptr<GenericArgument> argument) {
  arguments[flag] = argument;
}

void ArgumentRegistry::remove(std::string flag) { arguments.erase(flag); }

void ArgumentRegistry::update(std::string flag,
                              std::shared_ptr<GenericArgument> argument) {
  arguments[flag] = argument;
}

std::shared_ptr<GenericArgument> ArgumentRegistry::get(std::string flag) {
  return arguments[flag];
}

const std::unordered_map<std::string, std::shared_ptr<GenericArgument>>
ArgumentRegistry::get_all() {
  return arguments;
}