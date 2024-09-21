#include "./EncodingTune.h"

#include <string>

#include "../../enums/Tunes.h"
#include "../BaseArgument.h"

EncodingTune::EncodingTune(void)
    : BaseArgument<Tunes::Tune>("-t", "--tune", "Tune", Tunes::Tune::DEFAULT) {
  value = Tunes::Tune::DEFAULT;
  helpMessage = "Tune for the encoding process.";
}

EncodingTune::~EncodingTune(void) {}

void EncodingTune::parse(std::string provided) {
  Tunes::Tune tune = Tunes::getKey(provided);

  if (tune == Tunes::Tune::DEFAULT) {
    this->setErrored(true);
    return;
  }

  value = tune;
}