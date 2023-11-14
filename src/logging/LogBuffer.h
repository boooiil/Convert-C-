#if !defined(LOG_BUFFER)
#define LOG_BUFFER

#include <string>

class LogBuffer {
 public:
  /** This constructor should not be used. */
  LogBuffer(void);

  /**
   * @brief Construct a new Log Buffer object
   *
   * @param max The maximum number of lines to store.
   */
  LogBuffer(int max);
  ~LogBuffer(void);

  /**
   * @brief Add a line to the buffer.
   *
   * @param line The line to add.
   */
  void addLine(std::string);

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
   * @return std::string The output of the buffer.
   */
  std::string output(void);

 private:
  int current;
  int max;
  std::string line;
};

#endif  // LOG_BUFFER
