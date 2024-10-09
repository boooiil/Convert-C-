#ifndef PROGRAM_H
#define PROGRAM_H

#include <nlohmann/json.hpp>

#include "../utils/logging/Logger.h"
#include "generics/JSONSerializableRunner.h"
#include "settings/Settings.h"

class Program : public JSONSerializableRunner {
 public:
  static Settings* settings;
  // static Log* log;
  static JSONSerializableRunner* ticker;
  static bool stopFlag;

  Program(void);
  ~Program(void);

  void prepare(void);
  void prepare(int argc, char* argv[]);
  void run(void);
  void end(void);

  void setEndable(bool);
  bool isEndable(void);

  void fromJSON(nlohmann::json);
  nlohmann::json toJSON(void);

 private:
  bool endable;
};

#endif  // !PROGRAM_H