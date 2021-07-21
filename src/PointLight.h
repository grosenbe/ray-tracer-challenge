#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Color.h"
#include "Material.h"
#include "Tuple.h"

namespace RTC {
class PointLight {
 public:
  PointLight(const Tuple &, const Color &);
  Tuple
  GetPosition() const { return position; }

  Color
  GetIntensity() const { return intensity; }

 private:
  Tuple position;
  Color intensity;
};

Color Lighting(const Material &, const PointLight &, const Tuple &, const Tuple &, const Tuple &);
}  // namespace RTC
#endif
