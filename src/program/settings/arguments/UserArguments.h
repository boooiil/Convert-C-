/*********************************************************************
 * @file   UserArguments.h
 * @brief  User arguments class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef USER_ARGUMENTS_H
#define USER_ARGUMENTS_H

/**
 * @brief Parse user arguments.
 */
class UserArguments {
 public:
  UserArguments();
  ~UserArguments();

  /**
   * @brief Parse user arguments.
   *
   * @param[in] container  - Ptr to the Container object.
   * @param[in] argc        - Number of arguments.
   * @param[in] argv        - Array of arguments.
   */
  static void parse(class Container* container, int argc, char* argv[]);

 private:
  /**
   * @brief Print invalid argument message.
   *
   * @param[in] argument    - Argument.
   */
  static void invalidArgument(const char* argument);
};

#endif  // !USER_ARGUMENTS_H
