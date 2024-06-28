#include "./DesiredEncoder.h"

DesiredEncoder::DesiredEncoder(void) : BaseArgument<Encoders::Codec>() {
  value = Encoders::Codec::HEVC;
  helpMessage = "Desired encoder for the output file.";
}

DesiredEncoder::~DesiredEncoder(void) {}

void DesiredEncoder::parse(std::string provided) {
  Encoders::Codec codec = Encoders::getKey(provided);

  if (codec == Encoders::Codec::INVALID) {
    errored = true;
    return;
  }

  value = codec;
}