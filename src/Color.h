#ifndef COLOR_H
#define COLOR_H

#include "Tuple.h"

namespace RTC {
class Color : public Tuple {
 public:
  Color(double, double, double);

  double
  red() const { return GetX(); }
  double
  green() const { return GetY(); }
  double
  blue() const { return GetZ(); }

  Color operator*(const Color &) const;
  Color operator*(const double) const;
  Color operator+(const Color &) const;
};
}  // namespace RTC
#endif
