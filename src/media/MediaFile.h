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

  /**
   * @brief Construct a new Media File object.
   *
   * @param[in] name - Name of the file.
   * @param[in] path - Path to the file (generally CWD).
   */
  MediaFile(std::string name, std::string path);

  ~MediaFile(void);

  /// @brief CWD
  std::string cwd;
  /// @brief Original filename with extension
  std::string originalFileName;
  /// @brief Original file path with filename and extension
  std::string originalFullPath;
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
  /// @brief File extension
  std::string ext;

  int number;          /// @brief Unsure?
  std::size_t size;    /// @brief File size in bytes
  int newSize;         /// @brief File size in bytes after conversion
  int validationSize;  /// @brief File size in bytes after conversion
  int quality;         /// @brief Quality of the file
  int season;          /// @brief Season number

  /**
   * @brief Rename the current media name to a standard format.
   *
   * @param[out] container - Ptr to the Container object.
   */
  void rename(void);

 private:
  /**
   * @brief Compile the path with filename.
   *
   * @param[in] cwd               - Current working directory.
   * @param[in] original_filename - The original file name.
   */
  void resolvePath(std::string original_filename, std::string cwd);

  /**
   * @brief Compile the extension.
   *
   * @param[in] original_filename - The original file name.
   */
  void resolveExtension(std::string original_filename);

  /**
   * @brief Compile the series.
   *
   * @param[in] series_match - Provided match from the regex.
   */
  void resolveSeries(std::string series_match);

  /**
   * @brief Compile the season.
   *
   * @param[in] season_match - Provided match from the regex.
   */
  void resolveSeason(std::string season_match);

  /**
   * @brief Compile the episode.
   *
   * @param[in] episode_match - Provided match from the regex.
   */
  void resolveEpisode(std::string episode_match);

  /**
   * @brief Compile the quality (this is unused).
   *
   * @param[in] original_filename - The original file name.
   */
  void resolveQuality(std::string original_filename);

  /**
   * @brief Compile the modified file name.
   *
   * @param[in] series      - Series name.
   * @param[in] season      - Season number.
   * @param[in] episode     - Episode number.
   * @param[in] quality     - Chosen quality.
   */
  void resolveModifiedFileName(std::string series, std::string season,
                               std::string episode, std::string quality);

  /**
   * @brief Compile the modified file name with extension.
   *
   * @param[in] modified_filename   - The modified file name.
   * @param[in] ext                 - The extension of the file.
   */
  void resolveModifiedFileNameExt(std::string modified_filename,
                                  std::string ext);

  /**
   * @brief Compile the rename path.
   *
   * @param[in] modified_filename   - The modified file name.
   * @param[in] extension           - The extension of the file.
   * @param[in] cwd                 - Current working directory.
   */
  void resolveRenamePath(std::string modified_filename, std::string extension,
                         std::string cwd);

  /**
   * @brief Compile the conversion name.
   *
   * @param[in] modified_filename   - The modified file name.
   * @param[in] extension           - The extension of the file.
   */
  void resolveConversionName(std::string modifiedFileName,
                             std::string extension);

  /**
   * @brief Compile the conversion path.
   *
   * @Path format: cwd/{series} season {season number}/converted_filename
   *
   * @param[in] conversion_filename - Filename obtained from
   * resolveConversionName.
   * @param[in] series              - Series name.
   * @param[in] season              - Season number.
   * @param[in] cwd                 - Current working directory.
   */
  void resolveConversionPath(std::string conversion_filename,
                             std::string series, std::string season,
                             std::string cwd);
};

#endif  // !MEDIA_FILE
