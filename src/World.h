#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "PointLight.h"
#include "Ray.h"
#include "Sphere.h"

namespace RTC {
class World {
 public:
  std::shared_ptr<PointLight> Light;

  std::vector<std::shared_ptr<Sphere>> Objects;
};

World default_world();

std::vector<intersection> intersect_world(const World &, const Ray &);

struct Computations {
 public:
  Computations();
  double t;
  std::shared_ptr<Sphere> object;
  Tuple point;
  Tuple eyev;
  Tuple normalv;

  bool inside;
};

Computations prepare_computations(const intersection &, const Ray &);

Color shade_hit(const World &, const Computations &);

Color color_at(const World &, const Ray &);
}  // namespace RTC
#endif
