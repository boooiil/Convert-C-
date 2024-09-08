#ifndef CHILD_H
#define CHILD_H

#include <nlohmann/json_fwd.hpp>
#include <queue>

#include "../generics/JSONSerializableRunner.h"
#include "./media/Media.h"

class Child : public JSONSerializableRunner {
 public:
  /// @brief Holds current media files being converted.
  std::queue<Media*> converting;
  /// @brief Holds media files that are waiting to be converted.
  std::queue<Media*> pending;

  /// @brief Prepares the child for conversion.
  void prepare(void);
  ///  @brief Runs the child's conversion process.
  void run(void);
  /// @brief Ends the child's conversion process.
  void end(void);

  void setEndable(bool);
  bool isEndable(void);

  void fromJSON(nlohmann::json);

  nlohmann::json asJSON(void);

 private:
  bool endable;
};

#endif  // !CHILD_H
