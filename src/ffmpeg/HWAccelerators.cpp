#include "HWAccelerators.h"

std::unordered_map<HWAccelerators::Accelerator, std::string> HWAccelerators::acceleratorMap = {
    {HWAccelerators::AMD, "amf"},
    {HWAccelerators::NVIDIA, "cuda"},
    {HWAccelerators::INTEL, "qsv"},
    {HWAccelerators::VULKAN, "vaapi"}};

HWAccelerators::HWAccelerators() {}
HWAccelerators::~HWAccelerators() {}

/**
 * @brief Get the value of the hardware accelerator to be used in FFMpeg
 * arguments.
 *
 * @param accelerator The hardware accelerator.
 * @return std::string The FFMpeg value of the hardware accelerator.
 */
std::string HWAccelerators::getValue(HWAccelerators::Accelerator accelerator) {
  return acceleratorMap.at(accelerator);
}