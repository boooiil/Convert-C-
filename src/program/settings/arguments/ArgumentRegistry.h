#ifndef ARGUMENT_REGISTRY_H
#define ARGUMENT_REGISTRY_H

#include <memory>
#include <string>
#include <unordered_map>

#include "GenericArgument.h"

class ArgumentRegistry {
 public:
  static void add(std::string flag, std::shared_ptr<GenericArgument> argument);
  static void remove(std::string flag);
  static void update(std::string flag,
                     std::shared_ptr<GenericArgument> argument);
  static std::shared_ptr<GenericArgument> get(std::string flag);
  static const std::unordered_map<std::string, std::shared_ptr<GenericArgument>>
  get_all();

  template <typename T>
  static std::shared_ptr<T> get_t(std::string flag) {
    return std::dynamic_pointer_cast<T>(arguments[flag]);
  }

  using addFn = void (*)(std::string, std::shared_ptr<GenericArgument>);
  using removeFn = void (*)(std::string);
  using updateFn = void (*)(std::string, std::shared_ptr<GenericArgument>);
  using getFn = std::shared_ptr<GenericArgument> (*)(std::string);
  using getAllFn = const std::unordered_map<
      std::string, std::shared_ptr<GenericArgument>> (*)();

  template <typename T>
  using getTFn = std::shared_ptr<T> (*)(std::string);

 private:
  static std::unordered_map<std::string, std::shared_ptr<GenericArgument>>
      arguments;
};

#endif  // !ARGUMENT_REGISTRY_H
