#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>

#include <csignal>
#endif

#include "application/Container.h"
#include "application/Ticker.h"
#include "ffmpeg/ProbeResult.h"
#include "logging/Log.h"
#include "media/Media.h"
#include "media/MediaProcessStatistics.h"

/**
 * WALK AWAY NOTES:

 */

/**
 * ************************************* *
 *          CTRL / SIG HANDLERS          *
 * ************************************* *
 */

// weird wacky and uncool way of doing this
// TODO: maybe implement a better way of doing this when its complete

#ifdef _WIN32
BOOL WINAPI winHandle(DWORD signal) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  if (hConsole != INVALID_HANDLE_VALUE) {
    Ticker::end();

    DWORD bytesWritten;
    std::string message =
        "Interrupt signal (" + std::to_string(signal) + ") received.\n";

    WriteConsole(hConsole, message.c_str(), message.length(), &bytesWritten,
                 NULL);
  }

  exit(0);
}
#else
void unixHandle(int signum) {
  std::cout << "Interrupt signal (" << signum << ") received.\n";
  Ticker::end();

  exit(signum);
}
#endif

/**
 * ************************************* *
 *                  END                  *
 * ************************************* *
 */

/**
 * FINISH NOW, OPTIMIZE LATER
 * FINSIH NOW, OPTOIMIZE LATRE
 * FIFNEIH NOW, OETINMEN LENTER
 *
 * TODO: DOCUMENT, DOCUMENT, DOCUMENT
 */

/**
 * @brief Main
 *
 * @param argc Argument count
 * @param argv Argument values
 * @return int
 */
int main(int argc, char* argv[]) {
  Ticker::init();

  /**
   * ************************************* *
   *   CTRL / SIGTERM / SIGINT HANDLERS    *
   * ************************************* *
   */
#ifdef _WIN32
  // this DEFINITELY does not work
  SetConsoleCtrlHandler(winHandle, TRUE);
#else
  signal(SIGKILL, unixHandle);
  signal(SIGINT, unixHandle);
  signal(SIGTERM, unixHandle);
  signal(SIGQUIT, unixHandle);
#endif
  /**
   * ************************************* *
   *                 END                   *
   * ************************************* *
   */

  try {
    Ticker::container->userArguments.parse(Ticker::container, argc, argv);
    Ticker::container->userCapabilities.findHardwareDetails();
    Ticker::container->appEncodingDecision.validateSettings();

    Ticker::container->scanWorkingDir();

    Ticker::determineNextAction();

  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;

    Ticker::end();
  }

  return 0;
}
