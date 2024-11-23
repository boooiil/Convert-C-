#include "ProbeResultFormat.h"

#include <nlohmann/json.hpp>

#include "../../../../utils/logging/Logger.h"
#include "ProbeResultFormatTags.h"

ProbeResultFormat::ProbeResultFormat()
    : nb_programs(-1), nb_streams(-1), probe_score(-1) {}
ProbeResultFormat::~ProbeResultFormat() {}

ProbeResultFormat::ProbeResultFormat(nlohmann::json JSON)
    : nb_programs(-1), nb_streams(-1), probe_score(-1) {
  LOG_DEBUG("index: ", JSON.dump(4));

  if (!JSON["filename"].is_null()) {
    LOG_DEBUG("filename: ", JSON["filename"]);
    ProbeResultFormat::filename = JSON["filename"];
  }
  if (!JSON["nb_streams"].is_null()) {
    ProbeResultFormat::nb_streams = JSON["nb_streams"];
  }
  if (!JSON["nb_programs"].is_null()) {
    ProbeResultFormat::nb_programs = JSON["nb_programs"];
  }
  if (!JSON["format_name"].is_null()) {
    LOG_DEBUG("format_name: ", JSON["format_name"]);
    ProbeResultFormat::format_name = JSON["format_name"];
  }
  if (!JSON["format_long_name"].is_null()) {
    LOG_DEBUG("format_long_name: ", JSON["format_long_name"]);
    ProbeResultFormat::format_long_name = JSON["format_long_name"];
  }
  if (!JSON["start_time"].is_null()) {
    LOG_DEBUG("start_time: ", JSON["start_time"]);
    ProbeResultFormat::start_time = JSON["start_time"];
  }
  if (!JSON["duration"].is_null()) {
    LOG_DEBUG("duration: ", JSON["duration"]);
    ProbeResultFormat::duration = JSON["duration"];
  }
  if (!JSON["size"].is_null()) {
    LOG_DEBUG("size: ", JSON["size"]);
    ProbeResultFormat::size = JSON["size"];
  }
  if (!JSON["bit_rate"].is_null()) {
    LOG_DEBUG("bit_rate: ", JSON["bit_rate"]);
    ProbeResultFormat::bit_rate = JSON["bit_rate"];
  }
  if (!JSON["probe_score"].is_null()) {
    LOG_DEBUG("probe_score");
    ProbeResultFormat::probe_score = JSON["probe_score"];
  }

  ProbeResultFormat::tags = ProbeResultFormatTags(JSON["tags"]);
}