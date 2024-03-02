#include "./UserSettings.h"

#include "../../media/MediaDefinedFormat.h"

UserSettings::UserSettings(void) : validate(false){};

UserSettings::~UserSettings(void) {}

void UserSettings::validateSettings() {
  if (UserSettings::tune == Tunes::FILM &&
      Encoders::isHEVC(UserSettings::wantedEncoder)) {
    UserSettings::tune = Tunes::DEFAULT;
  }
}