#ifndef CHILD_CONVERSION_PROCESS_H
#define CHILD_CONVERSION_PROCESS_H

#include <nlohmann/json.hpp>

#include "../../../media/Media.h"

class ChildConversionProcess {
 public:
  ChildConversionProcess();
  ~ChildConversionProcess();

  std::list<Media> converting;
  std::list<Media> pending;

  void parse(nlohmann::json JSON);
};

#endif  // !CHILD_CONVERSION_PROCESS_H
