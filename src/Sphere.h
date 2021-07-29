#ifndef SPHERE_H
#define SPHERE_H

#include <memory>
#include <vector>

#include "Material.h"
#include "Matrix.h"
#include "Ray.h"

namespace RTC {
class Sphere {
 public:
  Sphere();
  Sphere(const Matrix &);
  Sphere(const Material &);
  Sphere(const Matrix &, const Material &);

  bool operator==(const Sphere &) const;

  void SetTransform(const Matrix &);
  Tuple normal_at(const Tuple &);

  Matrix transform;
  Material material;
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

Ray transform(const Ray &, const Matrix &);
}  // namespace RTC
#endif
