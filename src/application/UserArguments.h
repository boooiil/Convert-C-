#ifndef USER_ARGUMENTS
#define USER_ARGUMENTS

class UserArguments {
 public:
  UserArguments();
  ~UserArguments();

  static void parse(class Container*);

 private:
  static void invalidArgument(const char*);
};

#endif  // !USER_ARGUMENTS
