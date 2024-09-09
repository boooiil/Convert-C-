#include "./GPUProviders.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "../../../utils/ListUtils.h"

std::unordered_map<GPUProviders::Provider, std::string>
    GPUProviders::providerMap = {{NVIDIA, "nvidia"},
                                 {AMD, "amd"},
                                 {INTEL, "intel"},
                                 {UNKNOWN, "unknown"}};

GPUProviders::GPUProviders() {}
GPUProviders::~GPUProviders() {}

GPUProviders::Provider GPUProviders::getKey(std::string provider) {
  for (auto const& [key, val] : providerMap) {
    if (val == provider) {
      return key;
    }
  }
  return GPUProviders::UNKNOWN;
}

GPUProviders::Provider GPUProviders::getPreferred(
    std::vector<GPUProviders::Provider> providers) {
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

std::string GPUProviders::getValue(GPUProviders::Provider provider) {
  return providerMap.at(provider);
}