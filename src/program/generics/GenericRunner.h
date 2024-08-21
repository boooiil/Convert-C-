#ifndef GENERIC_RUNNER_H
#define GENERIC_RUNNER_H

class GenericRunner {
 public:
  virtual void prepare(void) = 0;
  virtual void run(void) = 0;
  virtual void end(void) = 0;
};

#endif  // !GENERIC_RUNNER_H
