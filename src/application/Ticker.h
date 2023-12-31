#ifndef TICKER_H
#define TICKER_H

#include "./Container.h"
#include "./Display.h"

class Ticker {
 public:
  static void init(Container*);
  static void start();
  static void end();

 private:
  static Container* container;
  static Display* display;

  static void writeDebug();
};

#endif  // !TICKER_H
