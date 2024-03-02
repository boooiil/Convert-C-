#ifndef OVERWRITE_EXISTING_H
#define OVERWRITE_EXISTING_H

#include "../FlagArgument.h"

class OverwriteExisting : public FlagArgument {
 public:
  OverwriteExisting(void);
  ~OverwriteExisting(void);

  void parse(std::string) override;

  OverwriteExisting& operator=(const bool& provided);
};

#endif  // OVERWRITE_EXISTING_H