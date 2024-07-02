#ifndef CHILD_H
#define CHILD_H

#include <queue>

#include "./media/Media.h"

class Child {
 public:
  Child(void);
  ~Child(void);

  /// @brief Holds current media files being converted.
  std::queue<Media*> converting;
  /// @brief Holds media files that are waiting to be converted.
  std::queue<Media*> pending;

  void prepare(void);
  void run(void);
  void end(void);
};

#endif  // !CHILD_H
