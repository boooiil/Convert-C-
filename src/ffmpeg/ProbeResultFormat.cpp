#include "ProbeResultFormat.h"

#include <iostream>

#include "../logging/Log.h"

ProbeResultFormat::ProbeResultFormat()
    : nb_programs(-1), nb_streams(-1), probe_score(-1) {}
ProbeResultFormat::~ProbeResultFormat() {}

ProbeResultFormat::ProbeResultFormat(nlohmann::json JSON) {
  Log::debug({"[ProbeResultFormat.cpp] filename: ", JSON["filename"]});
  Log::debug({"[ProbeResultFormat.cpp] json: ", JSON.dump(4)});
  Log::debug({"[ProbeResultFormat.cpp] size: ", JSON["size"]});
  ProbeResultFormat::filename = JSON["filename"];
  ProbeResultFormat::nb_streams = JSON["nb_streams"];
  ProbeResultFormat::nb_programs = JSON["nb_programs"];
  ProbeResultFormat::format_name = JSON["format_name"];
  ProbeResultFormat::format_long_name = JSON["format_long_name"];
  ProbeResultFormat::start_time = JSON["start_time"];
  ProbeResultFormat::duration = JSON["duration"];
  ProbeResultFormat::size = JSON["size"];
  ProbeResultFormat::bit_rate = JSON["bit_rate"];
  ProbeResultFormat::probe_score = JSON["probe_score"];

  ProbeResultFormat::tags = ProbeResultFormatTags(JSON["tags"]);
}