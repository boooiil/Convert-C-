/*********************************************************************
 * @file   Display.h
 * @brief  Display class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

#include "./Container.h"

/**
 * @brief Handles displaying information about the current program.
 */
class Display {
 public:
  /**
   * @brief Construct a new Display object
   *
   * @param[in] container - Ptr to the Container object.
   */
  Display(Container* container);
  ~Display(void);

  /**
   * @brief Prints the current state of the program.
   *
   */
  void print(void);

  /**
   * @brief Prints the current state of the program in debug mode.
   *
   */
  void printDebug(void);

  /**
   * @brief Prints the current state of the program in JSON format.
   *
   */
  void printJSON(void);

 private:
  /// @brief Container object.
  Container* container;
};

#endif  // !DISPLAY_H
