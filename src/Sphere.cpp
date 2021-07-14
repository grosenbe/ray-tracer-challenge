#include "Sphere.h"

#include <algorithm>
#include <cmath>

#include "Tuple.h"

using std::shared_ptr;
using std::vector;

using namespace RTC;

shared_ptr<Sphere>
RTC::sphere() {
  return std::make_shared<Sphere>();
}

Sphere::Sphere() : transform(Matrix::Identity(4)) {
}

void
Sphere::SetTransform(const Matrix &m) {
  transform = m;
}

std::vector<intersection>
RTC::intersect(std::shared_ptr<Sphere> s, const Ray &r) {
  auto r_transform = Transform(r, s->transform.Inv());
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
RTC::Transform(const Ray &r, const Matrix &m) {
  return Ray(m * r.origin, m * r.direction);
}
