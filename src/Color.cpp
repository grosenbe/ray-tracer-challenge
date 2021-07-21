#include "Color.h"

using namespace RTC;

Color::Color(double R, double G, double B) : RTC::Tuple(R, G, B, 0) {
}

Color
Color::operator*(const Color &other) const {
  return Color(GetX() * other.GetX(), GetY() * other.GetY(), GetZ() * other.GetZ());
}

Color
Color::operator*(double scale) const {
  return Color(red() * scale, green() * scale, blue() * scale);
}

Color
Color::operator+(const Color &other) const {
  return Color(red() + other.red(), green() + other.green(), blue() + other.blue());
}
