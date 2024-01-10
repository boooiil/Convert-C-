/*********************************************************************
 * @file   UserArguments.h
 * @brief  User arguments class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef USER_ARGUMENTS
#define USER_ARGUMENTS

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
   * @param[out] container  - Ptr to the Container object.
   * @param[in] argc        - Number of arguments.
   * @param[in] argv        - Array of arguments.
   */
  static void parse(class Container* container, int argc, char* argv[]);

 private:
  /**
   * @brief Print invalid argument message.
   *
   * @param[out] container  - Ptr to the Container object.
   * @param[in] argument    - Argument.
   */
  static void invalidArgument(class Container* container, const char* argument);
};

#endif  // !USER_ARGUMENTS
