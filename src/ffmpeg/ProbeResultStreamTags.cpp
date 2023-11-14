#include "ProbeResultStreamTags.h"

ProbeResultStreamTags::ProbeResultStreamTags() {}
ProbeResultStreamTags::~ProbeResultStreamTags() {}

ProbeResultStreamTags::ProbeResultStreamTags(nlohmann::json JSON) {
  ProbeResultStreamTags::title = JSON["title"];
  ProbeResultStreamTags::BPS = JSON["BPS"];
  ProbeResultStreamTags::NUMBER_OF_FRAMES = JSON["NUMBER_OF_FRAMES"];
  ProbeResultStreamTags::NUMBER_OF_BYTES = JSON["NUMBER_OF_BYTES"];
  ProbeResultStreamTags::_STATISTICS_WRITING_APP = JSON["_STATISTICS_WRITING_APP"];
  ProbeResultStreamTags::_STATISTICS_WRITING_DATE_UTC = JSON["_STATISTICS_WRITING_DATE_UTC"];
  ProbeResultStreamTags::_STATISTICS_TAGS = JSON["_STATISTICS_TAGS"];
  ProbeResultStreamTags::ENCODER = JSON["ENCODER"];
  ProbeResultStreamTags::DURATION = JSON["DURATION"];
}