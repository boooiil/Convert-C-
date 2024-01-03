/*********************************************************************
 * @file   MediaFile.h
 * @brief  MediaFile class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef MEDIA_FILE
#define MEDIA_FILE

#include <string>

/**
 * @brief Hold information about a media file.
 */
class MediaFile {
 public:
  /**
   * @brief Construct a new Media File object.
   *
   */
  MediaFile(void);
  ~MediaFile(void);

  /// @brief Filename after renaming without ext
  std::string modifiedFileName;
  /// @brief Filename after renaming including extension
  std::string modifiedFileNameExt;
  /// @brief Result of modifiedFileNameExt
  std::string conversionName;
  /// @brief Path resolving to cwd/{series} Season {##}/{conversionName}
  std::string conversionPath;
  /// @brief Path resolving to cwd/{modifiedFileNameExt}
  std::string renamePath;
  /// @brief Episode number in the series
  std::string episode;
  /// @brief Series name
  std::string series;
  /// @brief CWD
  std::string path;
  /// @brief File extension
  std::string ext;

  int number;          /// @brief Unsure?
  int size;            /// @brief File size in bytes
  int newSize;         /// @brief File size in bytes after conversion
  int validationSize;  /// @brief File size in bytes after conversion
  int quality;         /// @brief Quality of the file
  int season;          /// @brief Season number
};

#endif  // !MEDIA_FILE
