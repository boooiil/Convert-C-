#ifndef CROP_H
#define CROP_H

#include "../FlagArgument.h"

class Crop : public FlagArgument {
 public:
  Crop(void);
  ~Crop(void);

  void parse(std::string) override;

  Crop& operator=(const bool& provided) override;
};

#endif  // CROP_H