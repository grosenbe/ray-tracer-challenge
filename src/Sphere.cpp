#include "Sphere.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "Tuple.h"

using std::shared_ptr;
using std::vector;

using namespace RTC;

shared_ptr<Sphere>
RTC::sphere() {
  return std::make_shared<Sphere>();
}

Sphere::Sphere(const Matrix &m) {
  SetTransform(m);
}

Sphere::Sphere(const Material &m) {
  material = m;
  SetTransform(Matrix::Identity(4));
}

Sphere::Sphere(const Matrix &aMatrix, const Material &aMaterial) {
  SetTransform(aMatrix);
  material = aMaterial;
}

Sphere::Sphere() {
  SetTransform(Matrix::Identity(4));
}

void
Sphere::SetTransform(const Matrix &m) {
  // TODO make sure the matrix is the right size
  transform = m;
  transform.Inverse();
}

Tuple
Sphere::normal_at(const Tuple &worldPoint) {
  if (!worldPoint.IsPoint()) {
    throw std::runtime_error("Expected a point.");
  }

  auto objectPoint = transform.Inverse() * worldPoint;
  auto objectNormal = objectPoint - Tuple::MakePoint(0, 0, 0);
  auto worldNormal = transform.Inverse().Transpose() * objectNormal;
  auto normalized = worldNormal.Normalize();

  return Tuple::MakeVector(normalized.GetX(), normalized.GetY(), normalized.GetZ());
}

bool
Sphere::operator==(const Sphere &other) const {
  return transform == other.transform && material == other.material;
}

std::vector<intersection>
RTC::intersect(std::shared_ptr<Sphere> s, const Ray &r) {
  auto r_transform = transform(r, s->transform.Inverse());
  auto sphere_to_ray = r_transform.origin - Tuple::MakePoint(0, 0, 0);
  auto a = Dot(r_transform.direction, r_transform.direction);
  auto b = 2 * Dot(r_transform.direction, sphere_to_ray);
  auto c = Dot(sphere_to_ray, sphere_to_ray) - 1;

  auto discriminant = b * b - 4 * a * c;

  if (discriminant < 0)
    return std::vector<intersection>();

  return {
      intersection((-b - std::sqrt(discriminant)) / 2 / a, s),
      intersection((-b + std::sqrt(discriminant)) / 2 / a, s)};
}

intersection::intersection(double T, std::shared_ptr<Sphere> s) : t(T), object(s) {}

intersection
RTC::hit(vector<intersection> &Intersections) {
  auto it = Intersections.begin();
  while (it != Intersections.end()) {
    if (it->t < 0) {
      it = Intersections.erase(it);
    } else {
      ++it;
    }
  }

  if (Intersections.empty())
    return intersection(0, nullptr);

  std::sort(Intersections.begin(), Intersections.end(), [](intersection a, intersection b) { return a.t < b.t; });
  return *Intersections.begin();
}

Ray
RTC::transform(const Ray &r, const Matrix &m) {
  return Ray(m * r.origin, m * r.direction);
}
