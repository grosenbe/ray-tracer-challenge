#include <gtest/gtest.h>

#include "src/World.h"

using namespace RTC;

TEST(ch7tests, world) {
  World w = default_world();

  EXPECT_EQ(w.Light, PointLight(Tuple::MakePoint(-10, 10, -10), Color(1, 1, 1)));

  auto material = Material();
  material.color = Color(0.8, 1.0, 0.6);
  material.diffuse = 0.7;
  material.specular = 0.2;

  EXPECT_EQ(w.Objects[0], Sphere(material));
  EXPECT_EQ(w.Objects[1], Sphere(Scaling(0.5, 0.5, 0.5)));
}
