#ifndef GPU_PROVIDERS_H
#define GPU_PROVIDERS_H

#include <string>
#include <unordered_map>

class GPUProviders {
 public:
  GPUProviders();
  ~GPUProviders();

  enum Provider { NVIDIA, AMD, INTEL, UNKNOWN };

  /**
   * @brief Get the codec from a string.
   *
   * @param[in] codec - Desired codec.
   *
   * @return Codec enum.
   */
  static Provider getKey(std::string codec);

  /**
   * @brief Get the string value of the enum.
   *
   * @param[in] codec - Desired codec.
   *
   * @return String value of enum.
   */
  static std::string getValue(Provider codec);

 private:
  static std::unordered_map<Provider, std::string> providerMap;
};

#endif  // GPU_PROVIDERS_H