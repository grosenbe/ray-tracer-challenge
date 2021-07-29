#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "PointLight.h"
#include "Sphere.h"

namespace RTC {
class World {
 public:
  PointLight Light;

  std::vector<Sphere> Objects;
};

World default_world();
}  // namespace RTC
#endif
