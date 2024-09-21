#ifndef INTEGER_ARGUMENT_H
#define INTEGER_ARGUMENT_H

#include <stdexcept>
#include <string>

#include "../../../logging/Log.h"
#include "./BaseArgument.h"

class IntegerArgument : public BaseArgument<int> {
 public:
  IntegerArgument(std::string _helpMessage, std::string _flag,
                  std::string _longFlag, int data)
      : BaseArgument(_helpMessage, _flag, _longFlag, data) {}

  ~IntegerArgument() {}

  void parse(std::string argument) override {
    try {
      value = std::stoi(argument);
    } catch (std::invalid_argument& e) {
      Log::debug({e.what()});
      this->setErrored(true);
    }
  }

  virtual const std::string toString(void) const {
    return std::to_string(value);
  }
  virtual const bool hasData(void) const { return this->value != -1; }
};

#endif  // INTEGER_ARGUMENT_H