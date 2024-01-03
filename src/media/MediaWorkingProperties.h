/*********************************************************************
 * @file   MediaWorkingProperties.h
 * @brief  Media working properties header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/
#ifndef MEDIA_WORKING_PROPERTIES
#define MEDIA_WORKING_PROPERTIES

#include <string>

/**
 * @brief Holds information about the media working (conversion / validation
 * process) properties.
 */
class MediaWorkingProperties {
 public:
  /**
   * @brief Construct a new Media Working Properties object.
   *
   */
  MediaWorkingProperties(void);
  ~MediaWorkingProperties(void);

  float quality;  /// The QRF quality.
  float bitrate;  /// The encoding bitrate.
  float fps;      /// The speed of processing frames.

  ///  The number of frames that have been processed.
  int completedFrames;
};

#endif  // !MEDIA_WORKING_PROPERTIES
