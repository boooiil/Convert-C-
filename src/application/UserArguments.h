#ifndef USER_ARGUMENTS
#define USER_ARGUMENTS

class UserArguments {
 public:
  UserArguments();
  ~UserArguments();

  static void parse(class Container&, int argc, char* argv[]);

 private:
  static void invalidArgument(class Container&, const char*);
};

#endif  // !USER_ARGUMENTS
