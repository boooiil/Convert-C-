#include "GPUProviders.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "../../../utils/ListUtils.h"

const StringEnumDataHolder<GPUProviders> GPUProviders::UNKNOWN("unknown",
                                                               "Unknown");
const StringEnumDataHolder<GPUProviders> GPUProviders::NVIDIA("nvidia",
                                                              "Nvidia");
const StringEnumDataHolder<GPUProviders> GPUProviders::INTEL("intel", "Intel");
const StringEnumDataHolder<GPUProviders> GPUProviders::AMD("amd", "AMD");

const StringEnumDataHolder<GPUProviders> GPUProviders::getPreferred(
    std::vector<StringEnumDataHolder<GPUProviders>> providers) {
  if (ListUtils::contains(providers, NVIDIA)) {
    return NVIDIA;
  } else if (ListUtils::contains(providers, INTEL)) {
    return INTEL;
  } else if (ListUtils::contains(providers, AMD)) {
    return AMD;
  } else {
    return UNKNOWN;
  }
}