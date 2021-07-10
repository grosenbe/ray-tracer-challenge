#include <gtest/gtest.h>

#include "src/Ray.h"
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
