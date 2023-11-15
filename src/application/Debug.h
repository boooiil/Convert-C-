#if !defined(DEBUG)
#define DEBUG

class Debug {
 public:
  Debug();
  ~Debug();

  static bool toggle;
};

#endif  // DEBUG