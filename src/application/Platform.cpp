#include "Platform.h"

std::unordered_map<Platform::OS, std::string> Platform::osMap = {
    {Platform::OS::WINDOWS, "Windows"},
    {Platform::OS::LINUX, "Linux"},
    {Platform::OS::LINUX_LIKE, "Linux-like"},
    {Platform::OS::MAC, "Mac"},
    {Platform::OS::UNKNOWN, "Unknown"}};

Platform::Platform(void) {}
Platform::~Platform(void) {}

std::string Platform::getValue(OS os) { return osMap[os]; }