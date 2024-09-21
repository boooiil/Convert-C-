#ifndef QUALITY_H
#define QUALITY_H

#include <string>

#include "../../../child/media/MediaFormat.h"
#include "../BaseArgument.h"

class Quality : public BaseArgument<MediaFormat> {
 public:
  Quality(void);
  ~Quality(void);

  void parse(std::string) override;

  const std::string toString(void) const override;
  const bool hasData(void) const override;
};

#endif  // QUALITY_H