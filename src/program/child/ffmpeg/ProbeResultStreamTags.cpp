#include "ProbeResultStreamTags.h"

#include <nlohmann/json.hpp>

#include "../../../utils/logging/Logger.h"

ProbeResultStreamTags::ProbeResultStreamTags() {}
ProbeResultStreamTags::~ProbeResultStreamTags() {}

ProbeResultStreamTags::ProbeResultStreamTags(nlohmann::json JSON) {
  LOG_DEBUG("Starting ProbeResultStreamTags...");

  if (!JSON["language"].is_null()) {
    LOG_DEBUG("language: ", JSON["language"]);
    ProbeResultStreamTags::language = JSON["language"];
  }

  if (!JSON[title].is_null()) {
    LOG_DEBUG("title: ", JSON["title"]);
    ProbeResultStreamTags::title = JSON["title"];
  }

  if (!JSON["BPS"].is_null()) {
    LOG_DEBUG("BPS: ", JSON["BPS"]);
    ProbeResultStreamTags::BPS = JSON["BPS"];
  }

  if (!JSON["NUMBER_OF_FRAMES"].is_null()) {
    LOG_DEBUG("NUMBER_OF_FRAMES: ", JSON["NUMBER_OF_FRAMES"]);
    ProbeResultStreamTags::NUMBER_OF_FRAMES = JSON["NUMBER_OF_FRAMES"];
  }

  if (!JSON["NUMBER_OF_BYTES"].is_null()) {
    LOG_DEBUG("NUMBER_OF_BYTES: ", JSON["NUMBER_OF_BYTES"]);
    ProbeResultStreamTags::NUMBER_OF_BYTES = JSON["NUMBER_OF_BYTES"];
  }

  if (!JSON["_STATISTICS_WRITING_APP"].is_null()) {
    LOG_DEBUG("_STATISTICS_WRITING_APP: ", JSON["_STATISTICS_WRITING_APP"]);
    ProbeResultStreamTags::_STATISTICS_WRITING_APP =
        JSON["_STATISTICS_WRITING_APP"];
  }

  if (!JSON["_STATISTICS_WRITING_DATE_UTC"].is_null()) {
    LOG_DEBUG("_STATISTICS_WRITING_DATE_UTC: ",
              JSON["_STATISTICS_WRITING_DATE_UTC"]);
    ProbeResultStreamTags::_STATISTICS_WRITING_DATE_UTC =
        JSON["_STATISTICS_WRITING_DATE_UTC"];
  }

  if (!JSON["_STATISTICS_TAGS"].is_null()) {
    LOG_DEBUG("_STATISTICS_TAGS: ", JSON["_STATISTICS_TAGS"]);
    ProbeResultStreamTags::_STATISTICS_TAGS = JSON["_STATISTICS_TAGS"];
  }

  if (!JSON["ENCODER"].is_null()) {
    LOG_DEBUG("ENCODER: ", JSON["ENCODER"]);
    ProbeResultStreamTags::ENCODER = JSON["ENCODER"];
  }

  if (!JSON["DURATION"].is_null()) {
    LOG_DEBUG("DURATION: ", JSON["DURATION"]);
    ProbeResultStreamTags::DURATION = JSON["DURATION"];
  }

  LOG_DEBUG("Ended ProbeResultStreamTags");
}