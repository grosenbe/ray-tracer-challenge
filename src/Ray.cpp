#include "Ray.h"

#include <stdexcept>

using namespace RTC;

Ray::Ray(const Tuple &anOrigin, const Tuple &aDirection) : origin(anOrigin), direction(aDirection) {
  if (!origin.IsPoint())
    throw std::runtime_error("Origin needs to be a point.");

  if (!direction.IsVector())
    throw std::runtime_error("Direction needs to be a vector.");
}

Tuple
RTC::Position(const Ray &ray, const double t) {
  return ray.origin + ray.direction * t;
}
