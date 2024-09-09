/*********************************************************************
 * @file   Log.h
 * @brief  Log class header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#if !defined(LOG)
#define LOG

#include <initializer_list>
#include <string>

#include "LogBuffer.h"
#include "LogColor.h"

class Log {
 public:
  static void init(void);
  /**
   * @brief Sends a message to the console.
   *
   * @param[in] messages The messages to send to the console.
   *
   */
  static void send(std::initializer_list<std::string> messages);

  /**
   * @brief Sends a message to debug.
   *
   * @param[in] messages Messages to send to debug
   */
  static void debug(std::initializer_list<std::string> messages);

  /**
   * @brief Sends a message to the buffer.
   *
   * @param[in] length    - The length of the buffer
   * @param[in] messages  - The messages
   *
   * */
  // void sendBuffer(int, std::string);

  /**
   * @brief Sends a message to the buffer.
   *
   * @param[in] length    - The length of the buffer
   * @param[in] messages  - The messages
   *
   * */
  // void sendBuffer(int, const char*);

  /**
   * @brief Sends a message to the console in plain format.
   *
   * @param[in] messages - The messages
   *
   */
  void sendPlain(std::initializer_list<std::string> messages);

  static void end(void);

  /**
   * @brief Flushes the buffer.
   */
  void flushBuffer(void);

  /**
   * @brief Determines if buffer has messages.
   *
   * @return true if buffer has messages
   * @return false if buffer has no messages
   */
  bool hasBuffer(void);

 private:
  static LogBuffer* buffer;  /// @brief The buffer
};

#endif  // LOG
