#ifndef SPHERE_H
#define SPHERE_H

#include <memory>
#include <vector>

#include "Matrix.h"
#include "Ray.h"

namespace RTC {
class Sphere {
 public:
  Sphere();
  void SetTransform(const Matrix &);

  Matrix transform;
};

struct intersection {
  intersection(double, std::shared_ptr<Sphere>);

  bool
  operator==(const intersection &other) const {
    return other.t == t && other.object == object;
  }

  double t;
  std::shared_ptr<Sphere> object;
};

std::vector<intersection> intersect(std::shared_ptr<Sphere>, const Ray &);

std::shared_ptr<Sphere> sphere();

intersection hit(std::vector<intersection> &);

Ray Transform(const Ray &, const Matrix &);
}  // namespace RTC
#endif
