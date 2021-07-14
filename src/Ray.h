#ifndef RAY_H
#define RAY_H

#include <memory>

#include "Tuple.h"

namespace RTC {
class Ray {
 public:
  Ray(const Tuple &, const Tuple &);

  const Tuple origin;
  const Tuple direction;
};

Tuple Position(const Ray &, const double);
}  // namespace RTC
#endif
