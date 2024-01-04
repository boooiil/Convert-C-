#include "NumberUtils.h"

#include <iomanip>
#include <sstream>

std::string NumberUtils::formatNumber(float number, int digits) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(digits) << number;
  std::string resultString = oss.str();
  return resultString;
}

std::string NumberUtils::formatNumber(double number, int digits) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(digits) << number;
  std::string resultString = oss.str();
  return resultString;
}
