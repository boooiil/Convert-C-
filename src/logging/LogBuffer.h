/*********************************************************************
 * @file   LogBuffer.h
 * @brief  Log Buffer class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#if !defined(LOG_BUFFER)
#define LOG_BUFFER

#include <string>

/**
 * @brief A class to store the output of the log.
 */
class LogBuffer {
 public:
  /**
   * @brief Construct a new Log Buffer object
   *
   * @param[in] max - The maximum number of lines to store.
   */
  LogBuffer(int max);

  /**
   * @brief Add a line to the buffer.
   *
   * @param[in] line - The line to add.
   */
  void addLine(std::string line);

  /**
   * @brief Check if the buffer is full.
   *
   * @return true If the buffer is full.
   * @return false If the buffer is not full.
   */
  bool isFull(void);

  /**
   * @brief Get the output of the buffer.
   *
   * @return The output of the buffer.
   */
  std::string output(void);

 private:
  int current;       /// @brief The current number of lines in the buffer.
  int max;           /// @brief The maximum number of lines to store.
  std::string line;  /// @brief The line to add.
};

#endif  // LOG_BUFFER
