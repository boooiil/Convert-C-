#ifndef VALIDATE_H
#define VALIDATE_H

#include "../FlagArgument.h"

class Validate : public FlagArgument {
 public:
  Validate(void);
  ~Validate(void);

  /**
   * @brief Parse the validate argument.
   *
   * @param[in] argument - Argument.
   */
  void parse(std::string argument) override;

  /**
   * @brief Set the value of the validate argument.
   *
   * @param[in] provided - Value to set.
   * @return Validate& - Reference to the validate argument.
   */
  Validate& operator=(const bool& provided);
};

#endif  // VALIDATE_H