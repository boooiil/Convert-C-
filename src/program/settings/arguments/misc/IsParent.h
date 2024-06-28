#ifndef HAS_PARENT_H
#define HAS_PARENT_H

#include "../FlagArgument.h"

class IsParent : public FlagArgument {
 public:
  IsParent();
  ~IsParent();

  void parse(std::string argument) override;
  IsParent& operator=(const bool& provided) override;
};

#endif  // !HAS_PARENT_H
