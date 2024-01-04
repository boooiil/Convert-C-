/*********************************************************************
 * @file   Debug.h
 * @brief  Debug class header.
 *
 * @author boooiil
 * @date   January 2024
 *********************************************************************/

#if !defined(DEBUG)
#define DEBUG

/**
 * @brief Debug static class.
 */
class Debug {
 public:
  Debug();
  ~Debug();

  /// @brief Toggle debug mode.
  static bool toggle;
};

#endif  // DEBUG