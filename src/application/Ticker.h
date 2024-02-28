/*********************************************************************
 * @file   Ticker.h
 * @brief  Ticker class header file.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef TICKER_H
#define TICKER_H

#include "./Container.h"
#include "./Display.h"

/**
 * @brief Handles the main loop of the program.
 */
class Ticker {
 public:
  /// @brief Container object that holds all media objects.
  static Container* container;

  /// @brief Initializes the Ticker object.
  static void init();
  // @brief Determines the next action to take.
  static void determineNextAction();
  /// @brief Prints information about the process.
  static void printInformation();
  /// @brief Starts the main loop of the program.
  static void start();
  /// @brief Ends the main loop of the program.
  static void end();

 private:
  /// @brief Display object that handles the display.
  static Display* display;

  /// @brief Writes debug information to disk.
  static void writeDebug();
};

#endif  // !TICKER_H
