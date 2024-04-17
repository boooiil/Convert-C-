#include "./GPUProviders.h"

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

std::string GPUProviders::getValue(GPUProviders::Provider provider) {
  return providerMap.at(provider);
}