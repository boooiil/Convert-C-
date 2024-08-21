#include "NTicker.h"

#include "../Program.h"
#include "../child/display/ChildDisplay.h"
#include "../parent/display/ParentDisplay.h"
#include "../settings/Help.h"

void NTicker::determineNextAction(void) {
  // if (print help) display help
  // if (print information) print information
  //   print media information for child
  //   print directory informattion for parent
  // else start ticker
  // end ticker
}

void NTicker::prepare(void) {
  // use parent display
  if (Program::settings->argumentParser->isParent) {
    this->display = new ParentDisplay();
  } else {
    this->display = new ChildDisplay();
  }
}

void NTicker::start(void) {
  if (Program::settings->argumentParser->printHelp) {
    Help::printHelp();
  }

  while (true) {
  }
  if (Program::settings->argumentParser->isParent) {
    // parent display
    this->display->print();
  } else {
    // child display
    this->display->print();
  }
}

void NTicker::end(void) {
  if (this->display != nullptr) {
    delete this->display;
  }
}

void NTicker::writeDebug(void) {
  // write debug information
}
