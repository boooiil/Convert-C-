/*********************************************************************
 * @file   Media.h
 * @brief  Media class header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef MEDIA
#define MEDIA

#include <string>
#include <vector>

#include "../application/Activity.h"
#include "MediaFile.h"
#include "MediaVideoProperties.h"
#include "MediaWorkingProperties.h"

/**
 * @brief Media class.
 *
 * Trrr
 *
 */
class Media {
 public:
  /// @brief activity type
  Activity::ActivityType activity = Activity::WAITING;

  std::string path;  /// @brief cwd path
  std::string name;  /// @brief original filename

  /// @brief vector of arguments to be passed to ffmpeg
  std::vector<std::string> ffmpegArguments;
  long started;  /// @brief start time
  long ended;    /// @brief end time

  MediaFile file;                  /// @brief MediaFile object
  MediaVideoProperties video;      /// @brief MediaVideoProperties object
  MediaWorkingProperties working;  /// @brief MediaWorkingProperties object

  /**
   * @brief Create a Media object. (unused)
   *
   */
  Media();

  /**
   * @brief Create a Media object.
   *
   * @param[in] name - Name of the file.
   * @param[in] path - Path to the file (generally CWD).
   */
  Media(std::string name, std::string path);
  ~Media();

  /**
   * @brief Do the statistics process.
   *
   * @param[out] container - The container object.
   */
  void doStatistics(class Container& container);

  /**
   * @brief Do the conversion process.
   *
   * @param[out] container - The container object.
   */
  void doConversion(class Container& container);

  /**
   * @brief Do the validation process.
   *
   * @param[out] container - The container object.
   */
  void doValidation(class Container& container);

  /**
   * @brief Build arguments required to process FFmpeg media with given
   * parameters.
   *
   * @param[out] container  - The container object.
   * @param[in] isValidate  - TODO: I'm not sure what this does.
   */
  void buildFFmpegArguments(class Container& container, bool isValidate);

  /**
   * @brief Rename the current media name to a standard format.
   *
   * @param[out] container - The container object.
   */
  void rename(class Container& container);

  /**
   * @brief Check if the current media is processing.
   *
   * @return true if the media activity is STATISTICS, CONVERT or VALIDATE.
   * @return false if the media activity is WAITING-like, FINISHED, or
   * FAILED-like.
   */
  bool isProcessing(void);

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

#endif  // !MEDIA
