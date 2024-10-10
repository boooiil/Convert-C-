#include "Platform.h"

#include "StringEnumDataHolder.h"

const StringEnumDataHolder<Platform> Platform::UNKNOWN("unknown", "Unknown");
const StringEnumDataHolder<Platform> Platform::WINDOWS("windows", "Windows");
const StringEnumDataHolder<Platform> Platform::_LINUX("linux", "Linux");
const StringEnumDataHolder<Platform> Platform::LINUX_LIKE("linux-like",
                                                          "Linux like");
const StringEnumDataHolder<Platform> Platform::MACOS("macos", "MacOS");
