#ifndef ENCODING_TUNE_H
#define ENCODING_TUNE_H

#include "../../../ffmpeg/Tunes.h"
#include "../BaseArgument.h"

class EncodingTune : public BaseArgument<Tunes::Tune> {
 public:
  EncodingTune(void);
  ~EncodingTune(void);

  void parse(std::string) override;

  operator Tunes::Tune() const { return value; }
};

#endif  // ENCODING_TUNE_H