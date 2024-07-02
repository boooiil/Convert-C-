#ifndef PARENT_H
#define PARENT_H

#include <queue>

#include "child/ChildProcess.h"

class Parent {
 public:
  Parent(void);
  ~Parent(void);

  std::queue<ChildProcess*> childProcesses;

  void prepare(void);
  void run(void);
  void end(void);
};

#endif  // !PARENT_H