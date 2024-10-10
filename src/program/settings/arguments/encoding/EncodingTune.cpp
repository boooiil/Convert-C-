#include "EncodingTune.h"

#include <string>

#include "../../enums/StringEnumDataHolder.h"
#include "../../enums/Tunes.h"
#include "../BaseArgument.h"

EncodingTune::EncodingTune(void)
    : BaseArgument<StringEnumDataHolder<Tunes>>("-t", "--tune", "Tune",
                                                Tunes::DEFAULT) {
  value = Tunes::DEFAULT;
  helpMessage = "Tune for the encoding process.";
}

EncodingTune::~EncodingTune(void) {}

void EncodingTune::parse(std::string provided) {
  StringEnumDataHolder<Tunes> tune = Tunes::getKey(provided);

  if (tune == Tunes::DEFAULT) {
    this->setErrored(true);
    return;
  }

  value = tune;
}