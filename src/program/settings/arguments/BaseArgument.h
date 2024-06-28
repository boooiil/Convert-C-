#ifndef BASE_ARGUMENT_H
#define BASE_ARGUMENT_H

#include <string>

template <typename T>
class BaseArgument {
 public:
  virtual ~BaseArgument(void){};

  bool errored = false;

  /**
   * @brief Parse a given argument.
   *
   * @param[in] argument  - Argument.
   */
  virtual void parse(std::string) = 0;

  void set(const T& provided) { value = provided; }

  /**
   * @brief Get help message.
   *
   * @return Help message.
   */
  std::string getHelpMessage(void) { return helpMessage; };

  /**
   * @brief Get the value of this argument.
   *
   * @return Value of provided argument.
   */
  T get(void) { return value; };

  operator T(void) const { return value; }

  /**
   * @brief Set the value of this argument.
   *
   * @param[in] provided  Value to set.
   *
   * @return Reference to this object.
   */
  BaseArgument& operator=(const T& provided) {
    value = provided;
    return *this;
  };

 protected:
  /// @brief Help message for the argument.
  std::string helpMessage;
  /// @brief Value of provided argument.
  T value;
};

#endif  // BASE_ARGUMENT_H