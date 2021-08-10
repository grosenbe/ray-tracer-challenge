#include <gtest/gtest.h>

#include "src/Color.h"
#include "src/PointLight.h"
#include "src/Ray.h"
#include "src/Sphere.h"
#include "src/World.h"

using namespace RTC;

TEST(ch7tests, world) {
  World w = default_world();

  EXPECT_EQ(*(w.Light), PointLight(Tuple::MakePoint(-10, 10, -10), Color(1, 1, 1)));

  auto material = Material();
  material.color = Color(0.8, 1.0, 0.6);
  material.diffuse = 0.7;
  material.specular = 0.2;

  EXPECT_EQ(*(w.Objects[0]), Sphere(material));
  EXPECT_EQ(*(w.Objects[1]), Sphere(Scaling(0.5, 0.5, 0.5)));
}

TEST(ch7tests, intersections) {
  auto w = default_world();
  auto r = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 0, 1));

  auto xs = intersect_world(w, r);
  EXPECT_EQ(xs.size(), 4);
  EXPECT_EQ(xs[0].t, 4);
  EXPECT_EQ(xs[1].t, 4.5);
  EXPECT_EQ(xs[2].t, 5.5);
  EXPECT_EQ(xs[3].t, 6);
}

TEST(ch7tests, precomputation) {
  auto r = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 0, 1));
  auto shape = sphere();
  auto i = intersection(4, shape);

  auto comps = prepare_computations(i, r);
  EXPECT_EQ(comps.t, i.t);
  EXPECT_EQ(*(comps.object), *(i.object));
  EXPECT_EQ(comps.point, Tuple::MakePoint(0, 0, -1));
  EXPECT_EQ(comps.eyev, Tuple::MakeVector(0, 0, -1));
  EXPECT_EQ(comps.normalv, Tuple::MakeVector(0, 0, -1));
}

TEST(ch7tests, hits_inside) {
  // when an intersectin occurrs on the outside
  auto r = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 0, 1));
  auto shape = sphere();
  auto i = intersection(4, shape);
  auto comps = prepare_computations(i, r);
  EXPECT_FALSE(comps.inside);

  auto r2 = Ray(Tuple::MakePoint(0, 0, 0), Tuple::MakeVector(0, 0, 1));
  i = intersection(1, shape);
  comps = prepare_computations(i, r2);
  EXPECT_EQ(comps.point, Tuple::MakePoint(0, 0, 1));
  EXPECT_EQ(comps.eyev, Tuple::MakeVector(0, 0, -1));
  EXPECT_TRUE(comps.inside);
  EXPECT_EQ(comps.normalv, Tuple::MakeVector(0, 0, -1));
}

TEST(ch7tests, shading) {
  // shading an intersection
  auto w = default_world();
  auto r = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 0, 1));
  auto shape = w.Objects[0];
  auto i = intersection(4, shape);
  auto comps = prepare_computations(i, r);

  auto c = shade_hit(w, comps);
  EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));

  // shading an intersection from the inside
  w.Light = std::make_shared<PointLight>(Tuple::MakePoint(0, 0.25, 0), Color(1, 1, 1));
  auto r2 = Ray(Tuple::MakePoint(0, 0, 0), Tuple::MakeVector(0, 0, 1));
  auto shape2 = w.Objects[1];
  i = intersection(0.5, shape2);
  comps = prepare_computations(i, r2);
  c = shade_hit(w, comps);
  EXPECT_EQ(c, Color(0.90498, .90498, .90498));
}

TEST(ch7tests, color_at) {
  // when a ray misses
  auto w = default_world();
  auto r = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 1, 0));
  auto c = color_at(w, r);
  EXPECT_EQ(c, Color(0, 0, 0));

  // when a ray hits
  auto r2 = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 0, 1));
  c = color_at(w, r2);
  EXPECT_EQ(c, Color(.38066, .47583, .2855));

  // when the intersection is behind the ray
  auto outer = w.Objects[0];
  outer->material.ambient = 1;
  auto inner = w.Objects[1];
  inner->material.ambient = 1;
  auto r3 = Ray(Tuple::MakePoint(0, 0, 0.75), Tuple::MakeVector(0, 0, -1));
  auto c3 = color_at(w, r3);
  EXPECT_EQ(c3, inner->material.color);
}

TEST(ch7tests, viewTransformations) {
  auto from = Tuple::MakePoint(0, 0, 0);
  auto to = Tuple::MakePoint(0, 0, -1);
  auto up = Tuple::MakeVector(0, 1, 0);
  auto t = view_transformation(from, to, up);
  EXPECT_EQ(t, Matrix::Identity(4));

  to = Tuple::MakePoint(0, 0, 1);
  t = view_transformation(from, to, up);
  EXPECT_EQ(t, Scaling(-1, 1, -1));

  from = Tuple::MakePoint(0, 0, 8);
  to = Tuple::MakePoint(0, 0, 0);
  t = view_transformation(from, to, up);
  EXPECT_EQ(t, Translation(0, 0, -8));

  from = Tuple::MakePoint(1, 3, 2);
  to = Tuple::MakePoint(4, -2, 8);
  up = Tuple::MakeVector(1, 1, 0);
  t = view_transformation(from, to, up);

  EXPECT_EQ(t,
            Matrix({{-0.50709, 0.50709, 0.67612, -2.36643},
                    {0.76772, 0.60609, 0.12122, -2.82843},
                    {-0.35857, 0.59761, -0.71714, 0.00000},
                    {0.00000, 0.00000, 0.00000, 1.00000}}));
}
