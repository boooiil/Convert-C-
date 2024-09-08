#ifndef JSON_SERIALIZABLE_H
#define JSON_SERIALIZABLE_H

#include "nlohmann/json_fwd.hpp"

class JSONSerializable {
 public:
  virtual ~JSONSerializable() = default;

  virtual void fromJSON(const nlohmann::json) = 0;
  virtual const nlohmann::json toJSON() const = 0;
};

#endif  // !JSON_SERIALIZABLE_H
