#include "World.h"

#include <algorithm>
#include <cmath>
#include <memory>

#include "Color.h"
#include "Material.h"
#include "Matrix.h"
#include "PointLight.h"
#include "Ray.h"
#include "Tuple.h"

using namespace RTC;

World
RTC::default_world() {
  World w;

  w.Light = std::make_shared<PointLight>(Tuple::MakePoint(-10, 10, -10), Color(1, 1, 1));

  auto material = Material();
  material.color = Color(0.8, 1.0, 0.6);
  material.diffuse = 0.7;
  material.specular = 0.2;
  w.Objects.push_back(std::make_shared<Sphere>(material));
  w.Objects.push_back(std::make_shared<Sphere>(Scaling(0.5, 0.5, 0.5)));
  return w;
}

std::vector<intersection>
RTC::intersect_world(const World &aWorld, const Ray &aRay) {
  // iterate over all objects in the world, intersect with each ray, and aggregate the intersections
  // into a single object.
  std::vector<intersection> allIntersections;
  for (const auto &o : aWorld.Objects) {
    auto intersections = intersect(o, aRay);
    allIntersections.insert(allIntersections.end(), intersections.begin(), intersections.end());
  }

  std::sort(allIntersections.begin(), allIntersections.end(), [](const intersection &a, const intersection &b) { return a.t < b.t; });
  return allIntersections;
}

Computations::Computations() : t{-1}, object{nullptr}, point{Tuple::MakePoint(0, 0, 0)}, eyev{Tuple::MakeVector(0, 0, 0)}, normalv{Tuple::MakeVector(0, 0, 0)}, inside{false} {
}

Computations
RTC::prepare_computations(const intersection &anIntersection, const Ray &aRay) {
  Computations comps;

  comps.t = anIntersection.t;
  comps.object = anIntersection.object;

  comps.point = Position(aRay, comps.t);
  comps.eyev = aRay.direction * -1;
  comps.normalv = comps.object->normal_at(comps.point);

  if (Dot(comps.normalv, comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = comps.normalv * -1;
  } else {
    comps.inside = false;
  }
  return comps;
}

Color
RTC::shade_hit(const World &aWorld, const Computations &someComps) {
  return Lighting(someComps.object->material, *(aWorld.Light), someComps.point, someComps.eyev, someComps.normalv);
}

Color
RTC::color_at(const World &aWorld, const Ray &aRay) {
  // 1. Call intersect_world to find the intersections with the given world.
  // 2. Find the hit from the resulting intersections.
  // 3. Return black if there is no such intersection
  // 4. Otherwise, precompute the necessary values with prepare_computations
  // 5. Finally, call shade_hit to find the color at the hit

  auto intersections = intersect_world(aWorld, aRay);
  auto it = intersections.begin();
  while (it != intersections.end()) {
    if (it->t >= 0)
      break;

    ++it;
  }

  if (it == intersections.end())
    return Color(0, 0, 0);  // didn't find a hit

  auto comps = prepare_computations(*it, aRay);
  return shade_hit(aWorld, comps);
}
