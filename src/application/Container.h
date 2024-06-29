/*********************************************************************
 * @file   Container.h
 * @brief  Container class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef CONTAINER
#define CONTAINER

#include <queue>

#include "../logging/Log.h"
#include "../media/Media.h"
#include "./arguments/UserArguments.h"
#include "./settings/ProgramSettings.h"
#include "./settings/UserSettings.h"

/**
 * @brief Holds all media files necessary for running the application.
 * @brief Also holds application setttings and user arguments.
 */
class Container {
 public:
  Container(void);
  ~Container(void);

  Log log;

  UserArguments userArguments;
  UserSettings userSettings;
  ProgramSettings programSettings;

  /// @brief Holds current media file(s) being converted.
  std::queue<Media*> converting;
  /// @brief Holds media files that are waiting to be converted.
  std::queue<Media*> pending;

  // std::vector<Media*> mediaFiles;

  /**
   * Idea for above ^^^.
   *
   * Hold media files and then iterate through the list.
   */

  /**
   * @brief Scans working directory for media files and adds them to pending
   * queue.
   *
   */
  void scanWorkingDir(void);

  void scanChildDir(void);
};

#endif  // !CONTAINER
