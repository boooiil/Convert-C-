#include "Ticker.h"

#include <chrono>
#include <thread>

#include "../utils/RegexUtils.h"
#include "./Debug.h"

Ticker::Ticker(Container& container) : container(container) {
  Ticker::display = new Display(container);
}

Ticker::~Ticker() {
  container.log.debug({"[Ticker.cpp] deconstructing display"});
  delete Ticker::display;
}

void Ticker::start() {
  // once every second
  while (true) {
    int currentAmount = container.converting.size();

    container.log.send({std::to_string(currentAmount),
                        std::to_string(container.appEncodingDecision.amount)});

    if (currentAmount < container.appEncodingDecision.amount) {
      Media media = container.pending.front();

      if (media.activity != Activity::WAITING) {
        if (currentAmount == 0) {
          container.log.flushBuffer();
          if (Debug::toggle) {
            container.log.debug(
                {LogColor::fgRed("Debugging enabled. Writing debug file.")});
            // write debug contents matching that of Convert-JS
            container.log.debug({LogColor::fgRed("Debug file written.")});
            exit(0);
          } else
            exit(0);
        }
      } else {
        media.activity = Activity::WAITING_STATISTICS;

        // todo: this is probably going to be an issue at some point?
        // havent tested it, just making predictions
        media.started = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch())
                            .count();

        container.converting[media.name] = media;
        container.pending.pop();
      }
    }

    if (currentAmount > container.appEncodingDecision.amount) {
      container.log.send({LogColor::fgRed(
          "CURRENT TRANSCODES ARE GREATER THAN THE ALLOWED AMOUNT.")});

      container.log.send({LogColor::fgRed(
          "CURRENT ALLOWED AMOUNT: " +
          std::to_string(container.appEncodingDecision.amount))});

      container.log.send({LogColor::fgRed(
          "CURRENT QUEUE: " +
          std::to_string(container.appEncodingDecision.amount))});

      for (auto it = container.converting.begin();
           it != container.converting.end(); ++it) {
        Media value = it->second;
        container.log.send(
            {LogColor::fgRed("CURRENT FILE: " + value.file.modifiedFileName)});
      }
    }

    for (auto it = container.converting.begin();
         it != container.converting.end(); ++it) {
      Media media = it->second;

      container.log.send({media.name, Activity::getValue(media.activity)});

      if (!media.isProcessing()) {
        if (media.activity == Activity::WAITING_STATISTICS)
          media.doStatistics(container);
        if (media.activity == Activity::WAITING_CONVERT)
          media.doConversion(container);
        if (media.activity == Activity::WAITING_VALIDATE)
          media.doValidation(container);
      }

      if (RegexUtils::isMatch(Activity::getValue(media.activity),
                              "finished|failed", std::regex_constants::icase)) {
        // todo: again, chrono stuff
        media.ended = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();
      }
    }

    if (Debug::toggle)
      Ticker::display->printDebug();
    else
      Ticker::display->print();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}