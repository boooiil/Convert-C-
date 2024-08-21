#ifndef PROGRAM_H
#define PROGRAM_H

#include <nlohmann/json.hpp>

#include "../logging/Log.h"
#include "./ticker/NTicker.h"
#include "child/Child.h"
#include "generics/GenericRunner.h"
#include "generics/JSONSerializableRunner.h"
#include "parent/Parent.h"
#include "settings/Settings.h"

class Program : public JSONSerializableRunner {
 public:
  static Settings* settings;
  static JSONSerializableRunner* runner;
  static Log* log;
  static NTicker* ticker;

  static void prepare(void);
  static void run(int argc, char* argv[]);
  static void end(void);
  static nlohmann::json asJSON(void);
};

#endif  // !PROGRAM_H