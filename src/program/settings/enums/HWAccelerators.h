/*********************************************************************
 * @file   HWAccelerators.h
 * @brief  Hardware Accelerators enum and map.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#if !defined(HWACCELERATORS)
#define HWACCELERATORS

#include <string>
#include <unordered_map>

/**
 * @brief Class for HWAccelerators enum and map.
 *
 */
class HWAccelerators {
 public:
  HWAccelerators();
  ~HWAccelerators();

  /**
   * @brief Enum for hardware accelerators.
   *
   */
  enum Accelerator { NONE, AMD, NVIDIA, INTEL, VULKAN };

  /**
   * @brief Get the string value of the enum.
   *
   * @param[in] accelerator - Desired accelerator.
   *
   * @return String value of enum.
   */
  static std::string getValue(Accelerator accelerator);

 private:
  /**
   * @brief Map of enum to string value.
   *
   */
  static std::unordered_map<Accelerator, std::string> acceleratorMap;
};

#endif  // HWACCELERATORS
