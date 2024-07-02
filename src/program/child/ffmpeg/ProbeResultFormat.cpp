#include "ProbeResultFormat.h"

#include <nlohmann/json.hpp>

#include "../../../logging/Log.h"
#include "ProbeResultFormatTags.h"

ProbeResultFormat::ProbeResultFormat()
    : nb_programs(-1), nb_streams(-1), probe_score(-1) {}
ProbeResultFormat::~ProbeResultFormat() {}

ProbeResultFormat::ProbeResultFormat(nlohmann::json JSON)
    : nb_programs(-1), nb_streams(-1), probe_score(-1) {
  Log::debug({"[ProbeResultFormat.cpp] index: ", JSON.dump(4)});

  if (!JSON["filename"].is_null()) {
    Log::debug({"[ProbeResultFormat.cpp] filename: ", JSON["filename"]});
    ProbeResultFormat::filename = JSON["filename"];
  }
  if (!JSON["nb_streams"].is_null()) {
    ProbeResultFormat::nb_streams = JSON["nb_streams"];
  }
  if (!JSON["nb_programs"].is_null()) {
    ProbeResultFormat::nb_programs = JSON["nb_programs"];
  }
  if (!JSON["format_name"].is_null()) {
    Log::debug({"[ProbeResultFormat.cpp] format_name: ", JSON["format_name"]});
    ProbeResultFormat::format_name = JSON["format_name"];
  }
  if (!JSON["format_long_name"].is_null()) {
    Log::debug({"[ProbeResultFormat.cpp] format_long_name: ",
                JSON["format_long_name"]});
    ProbeResultFormat::format_long_name = JSON["format_long_name"];
  }
  if (!JSON["start_time"].is_null()) {
    Log::debug({"[ProbeResultFormat.cpp] start_time: ", JSON["start_time"]});
    ProbeResultFormat::start_time = JSON["start_time"];
  }
  if (!JSON["duration"].is_null()) {
    Log::debug({"[ProbeResultFormat.cpp] duration: ", JSON["duration"]});
    ProbeResultFormat::duration = JSON["duration"];
  }
  if (!JSON["size"].is_null()) {
    Log::debug({"[ProbeResultFormat.cpp] size: ", JSON["size"]});
    ProbeResultFormat::size = JSON["size"];
  }
  if (!JSON["bit_rate"].is_null()) {
    Log::debug({"[ProbeResultFormat.cpp] bit_rate: ", JSON["bit_rate"]});
    ProbeResultFormat::bit_rate = JSON["bit_rate"];
  }
  if (!JSON["probe_score"].is_null()) {
    Log::debug({"[ProbeResultFormat.cpp] probe_score"});
    ProbeResultFormat::probe_score = JSON["probe_score"];
  }

  ProbeResultFormat::tags = ProbeResultFormatTags(JSON["tags"]);
}