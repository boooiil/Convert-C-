#include "./DesiredEncoder.h"

#include <string>

#include "../../enums/Encoders.h"
#include "../BaseArgument.h"

DesiredEncoder::DesiredEncoder(void)
    : BaseArgument("-e", "--encoder", "Desired Encoder",
                   Encoders::Codec::HEVC) {
  value = Encoders::Codec::HEVC;
  helpMessage = "Desired encoder for the output file.";
}

DesiredEncoder::~DesiredEncoder(void) {}

void DesiredEncoder::parse(std::string provided) {
  Encoders::Codec codec = Encoders::getKey(provided);

  if (codec == Encoders::Codec::INVALID) {
    this->setErrored(true);
    return;
  }

  value = codec;
}

const std::string DesiredEncoder::toString(void) const {
  return Encoders::getValue(this->value);
}

const bool DesiredEncoder::hasData(void) const {
  return this->value != Encoders::INVALID;
}