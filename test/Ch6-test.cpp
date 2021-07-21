#include <gtest/gtest.h>

#include <cmath>

#include "src/Color.h"
#include "src/Material.h"
#include "src/Matrix.h"
#include "src/PointLight.h"
#include "src/Sphere.h"
#include "src/Tuple.h"

using namespace RTC;

TEST(ch6tests, spheres) {
  auto s = sphere();

  EXPECT_EQ(s->normal_at(Tuple::MakePoint(1, 0, 0)), Tuple::MakeVector(1, 0, 0));
  EXPECT_EQ(s->normal_at(Tuple::MakePoint(0, 1, 0)), Tuple::MakeVector(0, 1, 0));
  EXPECT_EQ(s->normal_at(Tuple::MakePoint(0, 0, 1)), Tuple::MakeVector(0, 0, 1));
  auto v = std::sqrt(3) / 3;
  auto n = s->normal_at(Tuple::MakePoint(v, v, v));
  EXPECT_EQ(n, Tuple::MakeVector(v, v, v));
  EXPECT_EQ(n, n.Normalize());

  s->SetTransform(Translation(0, 1, 0));
  auto n2 = s->normal_at(Tuple::MakePoint(0, 1 + std::sqrt(2) / 2, -std::sqrt(2) / 2));
  auto v2 = Tuple::MakeVector(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
  EXPECT_EQ(n2, v2);

  auto s2 = sphere();
  s2->SetTransform(Scaling(1, 0.5, 1) * RotationZ(M_PI / 5));
  EXPECT_EQ(s2->normal_at(Tuple::MakePoint(0, std::sqrt(2) / 2, -std::sqrt(2) / 2)), Tuple::MakeVector(0, 0.97014, -0.24254));

  EXPECT_EQ(s2->material, Material());

  // a sphere may be assigned a material
  Material m;
  m.ambient = 1;
  s2->material = m;
  EXPECT_EQ(s2->material, m);
}

TEST(ch6tests, tuples) {
  auto v = Tuple::MakeVector(1, -1, 0);
  auto n = Tuple::MakeVector(0, 1, 0);
  auto p = Tuple::MakePoint(1, 1, 1);
  EXPECT_ANY_THROW(Reflect(p, n));
  EXPECT_EQ(Reflect(v, n), Tuple::MakeVector(1, 1, 0));

  auto v2 = Tuple::MakeVector(0, -1, 0);
  auto n2 = Tuple::MakeVector(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);
  EXPECT_EQ(Reflect(v2, n2), Tuple::MakeVector(1, 0, 0));
}

TEST(ch6tests, lights) {
  Color intensity(1, 1, 1);
  auto position = Tuple::MakePoint(0, 0, 0);
  auto light = PointLight(position, intensity);
  EXPECT_EQ(light.GetPosition(), position);
  EXPECT_EQ(light.GetIntensity(), intensity);
}

TEST(ch6tests, material) {
  Material m;
  EXPECT_EQ(m.color, Color(1, 1, 1));
  EXPECT_EQ(m.ambient, 0.1);
  EXPECT_EQ(m.diffuse, 0.9);
  EXPECT_EQ(m.specular, 0.9);
  EXPECT_EQ(m.shininess, 200);

  auto position = Tuple::MakePoint(0, 0, 0);
  // lighting with the eye between the light and surface
  auto eyev = Tuple::MakeVector(0, 0, -1);
  auto normalv = Tuple::MakeVector(0, 0, -1);
  auto light = PointLight(Tuple::MakePoint(0, 0, -10), Color(1, 1, 1));
  EXPECT_EQ(Lighting(m, light, position, eyev, normalv), Color(1.9, 1.9, 1.9));

  // light with the eye 45 degrees offset from the surface
  auto eyev2 = Tuple::MakeVector(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
  EXPECT_EQ(Lighting(m, light, position, eyev2, normalv), Color(1.0, 1.0, 1.0));

  // light with the light 45 degrees offset from the surface
  auto light2 = PointLight(Tuple::MakePoint(0, 10, -10), Color(1, 1, 1));
  EXPECT_EQ(Lighting(m, light2, position, eyev, normalv), Color(0.7364, 0.7364, 0.7364));

  // light with the eye 45 degrees above the surface, and the eye 45 degrees below (in the path of the reflection vector)
  auto eyev3 = Tuple::MakeVector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
  EXPECT_EQ(Lighting(m, light2, position, eyev3, normalv), Color(1.6364, 1.6364, 1.6364));

  auto light3 = PointLight(Tuple::MakePoint(0, 0, 10), Color(1, 1, 1));
  EXPECT_EQ(Lighting(m, light3, position, eyev, normalv), Color(0.1, 0.1, 0.1));
}
