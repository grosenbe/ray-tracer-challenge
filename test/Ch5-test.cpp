#include <gtest/gtest.h>

#include "src/Matrix.h"
#include "src/Ray.h"
#include "src/Sphere.h"
#include "src/Tuple.h"

using namespace RTC;

TEST(ch5tests, createRay) {
  auto ray = Ray(Tuple::MakePoint(1, 2, 3), Tuple::MakeVector(4, 5, 6));
  EXPECT_EQ(ray.origin, Tuple::MakePoint(1, 2, 3));
  EXPECT_EQ(ray.direction, Tuple::MakeVector(4, 5, 6));

  auto ray2 = Ray(Tuple::MakePoint(2, 3, 4), Tuple::MakeVector(1, 0, 0));
  EXPECT_EQ(Position(ray2, 0), Tuple::MakePoint(2, 3, 4));
  EXPECT_EQ(Position(ray2, 1), Tuple::MakePoint(3, 3, 4));
  EXPECT_EQ(Position(ray2, -1), Tuple::MakePoint(1, 3, 4));
  EXPECT_EQ(Position(ray2, 2.5), Tuple::MakePoint(4.5, 3, 4));
}

TEST(ch5tests, spheres) {
  auto r = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 0, 1));
  auto s = sphere();
  auto xs = intersect(s, r);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].t, 4.0);
  EXPECT_EQ(xs[1].t, 6.0);

  // tangent
  auto r2 = Ray(Tuple::MakePoint(0, 1, -5), Tuple::MakeVector(0, 0, 1));
  xs = intersect(s, r2);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].t, 5.0);
  EXPECT_EQ(xs[1].t, 5.0);

  // miss
  auto r3 = Ray(Tuple::MakePoint(0, 2, -5), Tuple::MakeVector(0, 0, 1));
  xs = intersect(s, r3);
  EXPECT_EQ(xs.size(), 0);

  // inside the sphere
  auto r4 = Ray(Tuple::MakePoint(0, 0, 0), Tuple::MakeVector(0, 0, 1));
  xs = intersect(s, r4);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].t, -1.0);
  EXPECT_EQ(xs[1].t, 1.0);

  // "in front" of the sphere
  auto r5 = Ray(Tuple::MakePoint(0, 0, 5), Tuple::MakeVector(0, 0, 1));
  xs = intersect(s, r5);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].t, -6.0);
  EXPECT_EQ(xs[1].t, -4.0);
}

TEST(ch5tests, intersections) {
  auto s = sphere();
  auto i = intersection(3.5, s);
  EXPECT_EQ(i.t, 3.5);
  EXPECT_EQ(i.object, s);

  auto r = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 0, 1));
  auto xs = intersect(s, r);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].object, s);
  EXPECT_EQ(xs[1].object, s);
}

TEST(ch5tests, intersections2) {
  auto s = sphere();
  auto i1 = intersection(1, s);
  auto i2 = intersection(2, s);

  std::vector<intersection> xs{i1, i2};
  EXPECT_EQ(hit(xs), i1);
  xs.clear();

  i1 = intersection(-1, s);
  i2 = intersection(1, s);
  xs.push_back(i1);
  xs.push_back(i2);
  EXPECT_EQ(hit(xs), i2);
  xs.clear();

  i1 = intersection(-2, s);
  i2 = intersection(-1, s);
  xs.push_back(i1);
  xs.push_back(i2);
  auto i = hit(xs);
  EXPECT_FALSE(i.object);  // expect hit(xs) to return nothing
  xs.clear();

  i1 = intersection(5, s);
  i2 = intersection(7, s);
  auto i3 = intersection(-3, s);
  auto i4 = intersection(2, s);
  xs.push_back(i1);
  xs.push_back(i2);
  xs.push_back(i3);
  xs.push_back(i4);
  EXPECT_EQ(hit(xs), i4);
}

TEST(ch5tests, rays) {
  auto r = Ray(Tuple::MakePoint(1, 2, 3), Tuple::MakeVector(0, 1, 0));
  auto m = Translation(3, 4, 5);
  auto r2 = Transform(r, m);
  EXPECT_EQ(r2.origin, Tuple::MakePoint(4, 6, 8));
  EXPECT_EQ(r2.direction, Tuple::MakeVector(0, 1, 0));

  auto m2 = Scaling(2, 3, 4);
  auto r3 = Transform(r, m2);
  EXPECT_EQ(r3.origin, Tuple::MakePoint(2, 6, 12));
  EXPECT_EQ(r3.direction, Tuple::MakeVector(0, 3, 0));
}

TEST(ch5tests, sphere_transforms) {
  auto s = sphere();
  EXPECT_EQ(s->transform, Matrix::Identity(4));

  auto t = Translation(2, 3, 4);
  s->SetTransform(t);
  EXPECT_EQ(s->transform, t);
}

TEST(ch5tests, scaled_sphere_ray_intersection) {
  auto r = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 0, 1));
  auto s = sphere();

  s->SetTransform(Scaling(2, 2, 2));
  auto xs = intersect(s, r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].t, 3);
  EXPECT_EQ(xs[1].t, 7);
}

TEST(ch5tests, translated_sphere_ray_intersection) {
  auto r = Ray(Tuple::MakePoint(0, 0, -5), Tuple::MakeVector(0, 0, 1));
  auto s = sphere();

  s->SetTransform(Translation(5, 0, 0));
  auto xs = intersect(s, r);

  EXPECT_EQ(xs.size(), 0);
}
