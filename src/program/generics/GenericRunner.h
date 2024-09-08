#ifndef GENERIC_RUNNER_H
#define GENERIC_RUNNER_H

#include <type_traits>

class GenericRunner {
 public:
  virtual void prepare(void) = 0;
  virtual void run(void) = 0;
  virtual void end(void) = 0;

  virtual void setEndable(bool flag) = 0;
  virtual bool isEndable(void) = 0;

  template <typename T>
  T* getRunner(void) {
    static_assert(std::is_base_of<GenericRunner, T>::value,
                  "T must be a subclass of GenericRunner");
    return dynamic_cast<T*>(this);
  };
};

#endif  // !GENERIC_RUNNER_H
