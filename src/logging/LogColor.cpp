#include "LogColor.h"

LogColor::LogColor() {}
LogColor::~LogColor() {}

// terminal related
std::string LogColor::reset(std::string str) {
  return "\033[0m" + str + "\x1b[0m";
}
std::string LogColor::bright(std::string str) {
  return "\033[1m" + str + "\x1b[0m";
}
std::string LogColor::dim(std::string str) {
  return "\033[2m" + str + "\x1b[0m";
}
std::string LogColor::underscore(std::string str) {
  return "\033[4m" + str + "\x1b[0m";
}
std::string LogColor::blink(std::string str) {
  return "\033[5m" + str + "\x1b[0m";
}
std::string LogColor::reverse(std::string str) {
  return "\033[7m" + str + "\x1b[0m";
}
std::string LogColor::hidden(std::string str) {
  return "\033[8m" + str + "\x1b[0m";
}
std::string LogColor::none(std::string str) {
  return "\033[0m" + str + "\x1b[0m";
}

// text color
std::string LogColor::fgBlack(std::string str) {
  return "\033[30m" + str + "\x1b[0m";
}
std::string LogColor::fgRed(std::string str) {
  return "\033[31m" + str + "\x1b[0m";
}
std::string LogColor::fgGreen(std::string str) {
  return "\033[32m" + str + "\x1b[0m";
}
std::string LogColor::fgGray(std::string str) {
  return "\033[90m" + str + "\x1b[0m";
}
std::string LogColor::fgYellow(std::string str) {
  return "\033[33m" + str + "\x1b[0m";
}
std::string LogColor::fgBlue(std::string str) {
  return "\033[34m" + str + "\x1b[0m";
}
std::string LogColor::fgMagenta(std::string str) {
  return "\033[35m" + str + "\x1b[0m";
}
std::string LogColor::fgCyan(std::string str) {
  return "\033[36m" + str + "\x1b[0m";
}
std::string LogColor::fgWhite(std::string str) {
  return "\033[37m" + str + "\x1b[0m";
}

// background color
std::string LogColor::bgBlack(std::string str) {
  return "\033[40m" + str + "\x1b[0m";
}
std::string LogColor::bgRed(std::string str) {
  return "\033[41m" + str + "\x1b[0m";
}
std::string LogColor::bgGreen(std::string str) {
  return "\033[42m" + str + "\x1b[0m";
}
std::string LogColor::bgGray(std::string str) {
  return "\033[100m" + str + "\x1b[0m";
}
std::string LogColor::bgYellow(std::string str) {
  return "\033[43m" + str + "\x1b[0m";
}
std::string LogColor::bgBlue(std::string str) {
  return "\033[44m" + str + "\x1b[0m";
}
std::string LogColor::bgMagenta(std::string str) {
  return "\033[45m" + str + "\x1b[0m";
}
std::string LogColor::bgCyan(std::string str) {
  return "\033[46m" + str + "\x1b[0m";
}
std::string LogColor::bgWhite(std::string str) {
  return "\033[47m" + str + "\x1b[0m";
}
