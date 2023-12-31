#ifndef TICKER_H
#define TICKER_H

#include "./Container.h"
#include "./Display.h"

class Ticker {
 public:
  static Container* container;

  static void init();
  static void start();
  static void end();

 private:
  static Display* display;

  static void writeDebug();
};

#endif  // !TICKER_H
