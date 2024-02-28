#include "ProbeResultStreamTags.h"

#include "../logging/Log.h"

ProbeResultStreamTags::ProbeResultStreamTags() {}
ProbeResultStreamTags::~ProbeResultStreamTags() {}

ProbeResultStreamTags::ProbeResultStreamTags(nlohmann::json JSON) {
  Log::debug({"[ProbeResultStreamTags.cpp] Starting ProbeResultStreamTags..."});

  if (!JSON["language"].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] language: ", JSON["language"]});
    ProbeResultStreamTags::language = JSON["language"];
  }

  if (!JSON[title].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] title: ", JSON["title"]});
    ProbeResultStreamTags::title = JSON["title"];
  }

  if (!JSON["BPS"].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] BPS: ", JSON["BPS"]});
    ProbeResultStreamTags::BPS = JSON["BPS"];
  }

  if (!JSON["NUMBER_OF_FRAMES"].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] NUMBER_OF_FRAMES: ",
                JSON["NUMBER_OF_FRAMES"]});
    ProbeResultStreamTags::NUMBER_OF_FRAMES = JSON["NUMBER_OF_FRAMES"];
  }

  if (!JSON["NUMBER_OF_BYTES"].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] NUMBER_OF_BYTES: ",
                JSON["NUMBER_OF_BYTES"]});
    ProbeResultStreamTags::NUMBER_OF_BYTES = JSON["NUMBER_OF_BYTES"];
  }

  if (!JSON["_STATISTICS_WRITING_APP"].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] _STATISTICS_WRITING_APP: ",
                JSON["_STATISTICS_WRITING_APP"]});
    ProbeResultStreamTags::_STATISTICS_WRITING_APP =
        JSON["_STATISTICS_WRITING_APP"];
  }

  if (!JSON["_STATISTICS_WRITING_DATE_UTC"].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] _STATISTICS_WRITING_DATE_UTC: ",
                JSON["_STATISTICS_WRITING_DATE_UTC"]});
    ProbeResultStreamTags::_STATISTICS_WRITING_DATE_UTC =
        JSON["_STATISTICS_WRITING_DATE_UTC"];
  }

  if (!JSON["_STATISTICS_TAGS"].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] _STATISTICS_TAGS: ",
                JSON["_STATISTICS_TAGS"]});
    ProbeResultStreamTags::_STATISTICS_TAGS = JSON["_STATISTICS_TAGS"];
  }

  if (!JSON["ENCODER"].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] ENCODER: ", JSON["ENCODER"]});
    ProbeResultStreamTags::ENCODER = JSON["ENCODER"];
  }

  if (!JSON["DURATION"].is_null()) {
    Log::debug({"[ProbeResultStreamTags.cpp] DURATION: ", JSON["DURATION"]});
    ProbeResultStreamTags::DURATION = JSON["DURATION"];
  }

  Log::debug({"[ProbeResultStreamTags.cpp] Ended ProbeResultStreamTags"});
}