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

  Quality& operator=(const MediaFormat& provided);
};

#endif  // QUALITY_H