#ifndef JSON_SERIALIZABLE_RUNNER_H
#define JSON_SERIALIZABLE_RUNNER_H

#include "GenericRunner.h"
#include "nlohmann/json_fwd.hpp"

class JSONSerializableRunner : public GenericRunner {
 public:
  virtual ~JSONSerializableRunner(void) = default;
  virtual nlohmann::json asJSON(void) = 0;
};

#endif  // !JSON_SERIALIZABLE_RUNNER_H