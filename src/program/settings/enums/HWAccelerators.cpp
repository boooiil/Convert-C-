#include "HWAccelerators.h"

#include "StringEnumDataHolder.h"

const StringEnumDataHolder<HWAccelerators> HWAccelerators::NONE("none", "None");

const StringEnumDataHolder<HWAccelerators> HWAccelerators::AMD("opencl", "AMD");
const StringEnumDataHolder<HWAccelerators> HWAccelerators::NVIDIA("cuda",
                                                                  "NVIDIA");
const StringEnumDataHolder<HWAccelerators> HWAccelerators::INTEL("qsv",
                                                                 "Intel");
const StringEnumDataHolder<HWAccelerators> HWAccelerators::VULKAN("vaapi",
                                                                  "Vulkan");
