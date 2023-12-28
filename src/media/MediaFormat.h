#ifndef MEDIA_FORMAT
#define MEDIA_FORMAT

#include <string>

class MediaFormat {
 public:
  /**
   * @brief This constructor should not be used.
   *
   */
  MediaFormat();

  /**
   * @brief Construct a new Media Format object.
   *
   * @param name Name of the format.
   * @param crf Constant rate factor.
   * @param bitrate Bitrate of the format.
   * @param min Minimum bitrate of the format.
   * @param max Maximum bitrate of the format.
   * @param width Width of the format.
   * @param height Height of the format.
   * @param crop Crop of the format.
   * @param scale Scale of the format.
   */
  MediaFormat(std::string, int, double, double, double, int, int, std::string,
              std::string);
  ~MediaFormat();

  std::string name;
  std::string crop;
  std::string scale;

  int crf;
  double bitrate;
  double min;
  double max;
  int width;
  int height;

  /**
   * @brief Get the greatest common denominator of two numbers.
   *
   * @param a First number.
   * @param b Second number.
   * @return int Greatest common denominator.
   */
  static int getGCD(int, int);

  /**
   * @brief Get the resolution of the media.
   *
   * @param width Width of the media.
   * @param height Height of the media.
   * @param newWidth New width of the media.
   * @return int Resolution of the media.
   */
  static int getResolution(int, int, int);
};

#endif  // !MEDIA_FORMAT
