#include "./EncodingTune.h"

EncodingTune::EncodingTune(void) : BaseArgument<Tunes::Tune>() {
  value = Tunes::Tune::DEFAULT;
  helpMessage = "Tune for the encoding process.";
}

EncodingTune::~EncodingTune(void) {}

void EncodingTune::parse(std::string provided) {
  Tunes::Tune tune = Tunes::getKey(provided);

  if (tune == Tunes::Tune::DEFAULT) {
    errored = true;
    return;
  }

  value = tune;
}