
#ifndef GENERIC_ARGUMENT_H
#define GENERIC_ARGUMENT_H
#include <string>

class GenericArgument {
 public:
  GenericArgument() : errored(false) {}
  virtual ~GenericArgument() = default;
  virtual void parse(std::string argument) = 0;
  virtual std::string getHelpMessage(void) = 0;
  virtual std::string getLongFlag(void) = 0;
  virtual std::string getFlag(void) = 0;

  virtual const std::string toString(void) const = 0;
  virtual const bool hasData(void) const = 0;

  void setErrored(bool provided) { this->errored = provided; }
  const bool isErrored(void) { return this->errored; }

 private:
  bool errored;
};

#endif  // !GENERIC_ARGUMENT_H
