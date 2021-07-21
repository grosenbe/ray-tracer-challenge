#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

namespace RTC {
struct Material {
 public:
  Material();
  Color color;
  double ambient;
  double diffuse;
  double specular;
  double shininess;

  bool operator==(const Material&) const;
};

}  // namespace RTC
#endif
