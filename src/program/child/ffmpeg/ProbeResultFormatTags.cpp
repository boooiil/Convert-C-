#include "ProbeResultFormatTags.h"

#include <nlohmann/json.hpp>

#include "../../../logging/Log.h"

ProbeResultFormatTags::ProbeResultFormatTags() {}
ProbeResultFormatTags::~ProbeResultFormatTags() {}

ProbeResultFormatTags::ProbeResultFormatTags(nlohmann::json JSON) {
  Log::debug({"[ProbeResultFormatTags.cpp] starting format tags"});
  // ProbeResultFormatTags::ENCODER = JSON["ENCODER"];
}