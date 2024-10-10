#ifndef ENCODING_TUNE_H
#define ENCODING_TUNE_H

#include <string>

#include "../../enums/StringEnumDataHolder.h"
#include "../../enums/Tunes.h"
#include "../BaseArgument.h"

class EncodingTune : public BaseArgument<StringEnumDataHolder<Tunes>> {
 public:
  EncodingTune(void);
  ~EncodingTune(void);

  void parse(std::string) override;
};

#endif  // ENCODING_TUNE_H