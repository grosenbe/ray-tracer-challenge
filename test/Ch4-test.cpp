#include <gtest/gtest.h>

#include "src/Matrix.h"
#include "src/Tuple.h"

using namespace RTC;

TEST(ch4tests, translation) {
  auto transform = Translation(5, -3, 2);
  auto p = Tuple::MakePoint(-3, 4, 5);

  EXPECT_EQ((transform * p), Tuple::MakePoint(2, 1, 7));

  auto inv = transform.Inverse();
  EXPECT_EQ((inv * p), Tuple::MakePoint(-8, 7, 3));

  auto v = Tuple::MakeVector(-3, 4, 5);
  EXPECT_EQ(inv * v, v);
}

TEST(ch4tests, scaling) {
  auto transform = Scaling(2, 3, 4);
  auto p = Tuple::MakePoint(-4, 6, 8);

  EXPECT_EQ(transform * p, Tuple::MakePoint(-8, 18, 32));

  auto v = Tuple::MakeVector(-4, 6, 8);
  EXPECT_EQ(transform * v, Tuple::MakeVector(-8, 18, 32));

  auto reverse = transform.Inverse();
  EXPECT_EQ(reverse * v, Tuple::MakeVector(-2, 2, 2));
}

TEST(ch4tests, reflection) {
  auto transform = Scaling(-1, 1, 1);
  auto p = Tuple::MakePoint(2, 3, 4);
  EXPECT_EQ(transform * p, Tuple::MakePoint(-2, 3, 4));
}

TEST(ch4tests, rotationX) {
  auto p = Tuple::MakePoint(0, 1, 0);

  auto half_quarter = RotationX(PI_4);
  auto full_quarter = RotationX(PI_2);

  EXPECT_EQ(half_quarter * p, Tuple::MakePoint(0, SQRT2 / 2, SQRT2 / 2));
  EXPECT_EQ(full_quarter * p, Tuple::MakePoint(0, 0, 1));

  auto half_quarter_back = half_quarter.Inverse();
  EXPECT_EQ(half_quarter_back * p, Tuple::MakePoint(0, SQRT2 / 2, -SQRT2 / 2));
}

TEST(ch4tests, rotationY) {
  auto p = Tuple::MakePoint(0, 0, 1);

  auto half_quarter = RotationY(PI_4);
  auto full_quarter = RotationY(PI_2);

  EXPECT_EQ(half_quarter * p, Tuple::MakePoint(SQRT2 / 2, 0, SQRT2 / 2));
  EXPECT_EQ(full_quarter * p, Tuple::MakePoint(1, 0, 0));
}

TEST(ch4tests, rotationZ) {
  auto p = Tuple::MakePoint(0, 1, 0);

  auto half_quarter = RotationZ(PI_4);
  auto full_quarter = RotationZ(PI_2);

  EXPECT_EQ(half_quarter * p, Tuple::MakePoint(-SQRT2 / 2, SQRT2 / 2, 0));
  EXPECT_EQ(full_quarter * p, Tuple::MakePoint(-1, 0, 0));
}

TEST(ch4tests, shearing) {
  auto transform = Shearing(1, 0, 0, 0, 0, 0);
  auto p = Tuple::MakePoint(2, 3, 4);
  EXPECT_EQ(transform * p, Tuple::MakePoint(5, 3, 4));

  transform = Shearing(0, 1, 0, 0, 0, 0);
  EXPECT_EQ(transform * p, Tuple::MakePoint(6, 3, 4));

  transform = Shearing(0, 0, 1, 0, 0, 0);
  EXPECT_EQ(transform * p, Tuple::MakePoint(2, 5, 4));

  transform = Shearing(0, 0, 0, 1, 0, 0);
  EXPECT_EQ(transform * p, Tuple::MakePoint(2, 7, 4));

  transform = Shearing(0, 0, 0, 0, 1, 0);
  EXPECT_EQ(transform * p, Tuple::MakePoint(2, 3, 6));

  transform = Shearing(0, 0, 0, 0, 0, 1);
  EXPECT_EQ(transform * p, Tuple::MakePoint(2, 3, 7));
}

TEST(ch4tests, sequenceTransformations) {
  auto p = Tuple::MakePoint(1, 0, 1);
  auto A = RotationX(PI_2);
  auto B = Scaling(5, 5, 5);
  auto C = Translation(10, 5, 7);

  EXPECT_EQ(A.Inverse(), A.Transpose());
  EXPECT_EQ(A.Inverse(), A.Transpose());
  A.SetValue(1, 1, 1);
  A.SetValue(2, 2, 1);
  A.SetValue(2, 1, 0);
  A.SetValue(1, 2, 0);
  EXPECT_EQ(A.Inverse(), A.Transpose());
  A = RotationX(PI_2);

  auto p2 = A * p;
  EXPECT_EQ(p2, Tuple::MakePoint(1, -1, 0));

  auto p3 = B * p2;
  EXPECT_EQ(p3, Tuple::MakePoint(5, -5, 0));

  auto p4 = C * p3;
  EXPECT_EQ(p4, Tuple::MakePoint(15, 0, 7));

  auto T = C * B * A;
  EXPECT_EQ(T * p, Tuple::MakePoint(15, 0, 7));
}
