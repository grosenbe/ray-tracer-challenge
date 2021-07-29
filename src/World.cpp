#include "World.h"

#include "Material.h"
#include "Matrix.h"

using namespace RTC;

World
RTC::default_world() {
  World w;

  w.Light = PointLight(Tuple::MakePoint(-10, 10, -10), Color(1, 1, 1));

  auto material = Material();
  material.color = Color(0.8, 1.0, 0.6);
  material.diffuse = 0.7;
  material.specular = 0.2;
  w.Objects.push_back(Sphere(material));
  w.Objects.push_back(Sphere(Scaling(0.5, 0.5, 0.5)));
  return w;
}
