#ifndef TICKER_H
#define TICKER_H

#include "./Container.h"
#include "./Display.h"

class Ticker {
 public:
  Ticker(Container&);
  ~Ticker();

  void start();

 private:
  Container& container;
  Display* display;
};

#endif  // !TICKER_H
