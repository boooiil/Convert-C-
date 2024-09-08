#ifndef PROGRAM_H
#define PROGRAM_H

#include <nlohmann/json.hpp>

#include "../logging/Log.h"
#include "generics/JSONSerializableRunner.h"
#include "settings/Settings.h"

class Program : public JSONSerializableRunner {
 public:
  static Settings* settings;
  static Log* log;
  static JSONSerializableRunner* ticker;
  static bool stopFlag;

  static void prepare(int argc, char* argv[]);
  static void run(void);
  static void end(void);

  static void setEndable(bool);
  static bool isEndable(void);

  static void fromJSON(nlohmann::json);
  static nlohmann::json asJSON(void);

 private:
  bool endable;
};

#endif  // !PROGRAM_H