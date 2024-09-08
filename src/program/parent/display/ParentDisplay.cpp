#include "ParentDisplay.h"

#include "../../../logging/Log.h"
#include "../../Program.h"
#include "../../generics/GenericRunner.h"
#include "../../ticker/NTicker.h"
#include "../Parent.h"

void ParentDisplay::print(void) {
  // TODO: finish
}

void ParentDisplay::printDebug(void) {
  // TODO: finish
}

void ParentDisplay::printInformation(void) {
  Log::debug({"Printing Information"});

  NTicker* ticker = Program::ticker->getRunner<NTicker>();
  Parent* runner = ticker->runner->getRunner<Parent>();
}

void ParentDisplay::printJSON(void) {
  // TODO: finish
}
