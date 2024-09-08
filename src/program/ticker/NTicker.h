#ifndef NTICKER_H
#define NTICKER_H

#include <nlohmann/json_fwd.hpp>

#include "../generics/GenericDisplay.h"
#include "../generics/JSONSerializableRunner.h"

class NTicker : public JSONSerializableRunner {
 public:
  JSONSerializableRunner* runner;

  NTicker(void);
  void determineNextAction(void);
  void prepare(void);
  void run(void);
  void end(void);

  void setEndable(bool endable);
  bool isEndable(void);

  void fromJSON(nlohmann::json);
  nlohmann::json asJSON(void);

 private:
  bool endable;
  GenericDisplay* display;
  void writeDebug(void);
};

#endif  // !NTICKER_H