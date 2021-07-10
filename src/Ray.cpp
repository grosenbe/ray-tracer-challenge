#include "Ray.h"

using namespace RTC;

Ray::Ray(const Tuple &anOrigin, const Tuple &aDirection) : origin(anOrigin), direction(aDirection) {}

Tuple
RTC::Position(const Ray &ray, const double t) {
  return ray.origin + ray.direction * t;
}
