#if !defined(HWACCELERATORS)
#define HWACCELERATORS

#include <string>
#include <unordered_map>

class HWAccelerators {
 public:
  HWAccelerators();
  ~HWAccelerators();

  enum Accelerator { AMD, NVIDIA, INTEL, VULKAN };

  /**
   * @brief Get the string value of the enum.
   *
   * @param accelerator Desired accelerator.
   * @return std::string String value of enum.
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
