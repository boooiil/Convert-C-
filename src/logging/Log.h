#if !defined(LOG)
#define LOG

#include "LogBuffer.h"
#include "LogColor.h"

class Log {
 public:
  Log(void);
  ~Log(void);

  /**
   * @brief      Sends a message to the console.
   * *
   * * @param[in]  messages  The messages
   *
   */
  static void send(std::initializer_list<std::string>);

  /**
   * @brief      Sends a message to debug.
   *
   * @param[in]  Args...     Messages to send to debug
   */
  static void debug(std::initializer_list<std::string>);

  /**
   * @brief      Sends a message to the buffer.
   * *
   * * @param[in]  length    The length of the buffer
   * * @param[in]  messages  The messages
   *
   * */
  void sendBuffer(int, std::string);

  /**
   * @brief      Sends a message to the buffer.
   * *
   * * @param[in]  length    The length of the buffer
   * * @param[in]  messages  The messages
   *
   * */
  void sendBuffer(int, const char*);

  /**
   * @brief      Sends a message to the console in plain format.
   *
   * @param[in]  messages  The messages
   *
   */
  void sendPlain(std::initializer_list<std::string>);

  /**
   * @brief      Flushes the buffer.
   */
  void flushBuffer(void);

  /**
   * @brief      Determines if buffer has messages.
   *
   * @return     True if buffer has messages, False otherwise.
   */
  bool hasBuffer(void);

 private:
  LogBuffer* buffer;
};

#endif  // LOG
