#ifndef PROGRAM_H
#define PROGRAM_H

#include <nlohmann/json.hpp>

#include "../logging/Log.h"
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
  nlohmann::json asJSON(void);

 private:
  bool endable;
};

#endif  // !PROGRAM_H