#include "DesiredEncoder.h"

#include <string>

#include "../../enums/Encoders.h"
#include "../../enums/StringEnumDataHolder.h"
#include "../BaseArgument.h"

DesiredEncoder::DesiredEncoder(void)
    : BaseArgument("-e", "--encoder", "Desired Encoder", Encoders::HEVC) {}

DesiredEncoder::~DesiredEncoder(void) {}

void DesiredEncoder::parse(std::string provided) {
  StringEnumDataHolder<Encoders> codec = Encoders::getKey(provided);

  if (codec == Encoders::INVALID) {
    this->setErrored(true);
    return;
  }

  value = codec;
}

const std::string DesiredEncoder::toString(void) const {
  return this->value.getName();
}

const bool DesiredEncoder::hasData(void) const {
  return this->value != Encoders::INVALID;
}