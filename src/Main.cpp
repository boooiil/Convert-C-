#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <windows.h>

#include "./utils/signals/WindowsSignalHandler.h"

using SignalHandler = WindowsSignalHandler;

#else
#include "./utils/signals/UnixSignalHandler.h"

using SignalHandler = UnixSignalHandler;

#endif

#include <exception>
#include <iostream>

#include "program/Program.h"

/**
 * WALK AWAY NOTES:
 *
 * add option for modifying audio codec
 * add option for modifying audio channels
 *
 * create argument factory
 *
 * av1 does not support film tune
 *
 * Determine how to handle a parent class and how we
 * will be storing the data
 *
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
#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //_CrtSetBreakAlloc(0);

#endif
  try {
    SignalHandler sigHandler = SignalHandler();
    sigHandler.registerHandler();

    Program::prepare(argc, argv);

    Program::run();

  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  Program::end();

  return 0;
}
