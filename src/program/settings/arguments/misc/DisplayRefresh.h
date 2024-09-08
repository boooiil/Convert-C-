#ifndef DISPLAY_REFRESH_H
#define DISPLAY_REFRESH_H

#include <string>

#include "../IntegerArgument.h"

class DisplayRefresh : public IntegerArgument {
 public:
  DisplayRefresh(void);
  ~DisplayRefresh(void);

  void parse(std::string) override;
};
#endif  // !DISPLAY_REFRESH_H
