#ifndef START_AT_H
#define START_AT_H

#include <string>

#include "../StringArgument.h"

class StartAt : public StringArgument {
 public:
  StartAt();
  ~StartAt();

  /**
   * @brief Parse the start at argument.
   *
   * @param[in] argument - Argument.
   */
  void parse(std::string argument) override;
};

#endif  // START_AT_H