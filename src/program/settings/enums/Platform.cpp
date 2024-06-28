#include "Platform.h"

std::unordered_map<Platform::OPERATING_SYSTEM, std::string> Platform::osMap = {
    {Platform::OPERATING_SYSTEM::WINDOWS, "Windows"},
    {Platform::OPERATING_SYSTEM::_LINUX, "Linux"},
    {Platform::OPERATING_SYSTEM::LINUX_LIKE, "Linux-like"},
    {Platform::OPERATING_SYSTEM::MAC, "Mac"},
    {Platform::OPERATING_SYSTEM::UNKNOWN, "Unknown"}};

Platform::Platform(void) {}
Platform::~Platform(void) {}

std::string Platform::getValue(OPERATING_SYSTEM os) { return osMap[os]; }