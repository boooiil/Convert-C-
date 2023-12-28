#ifndef CONTAINER
#define CONTAINER

#include "../application/Settings.h"
#include "../application/UserArguments.h"
#include "../application/UserCapabilities.h"
#include "../logging/Log.h"
#include "../media/Media.h"
#include "ApplicationEncodingDecision.h"

class Container {
 public:
  Container();
  ~Container();

  Log log;

  ApplicationEncodingDecision appEncodingDecision;
  Settings settings;
  UserArguments userArguments;
  UserCapabilities userCapabilities;

  std::unordered_map<std::string, Media> converting;
  std::vector<Media> pending;

  void scanWorkingDir();
};

#endif  // !CONTAINER
