#ifndef CHILD_PROCESS_CONVERSION_H
#define CHILD_PROCESS_CONVERSION_H
#include <string>

#include "../../child/media/MediaProcess.h"
#include "ChildProcess.h"

class ChildProcessConversion : public MediaProcess<ChildProcess> {
 public:
  ChildProcessConversion(ChildProcess* childProcess);

  void parse(std::string data) override;
};

#endif  // !CHILD_PROCESS_CONVERSION_H
