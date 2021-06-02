#include <gtest/gtest.h>
#include <src/Matrix.h>
#include <src/Tuple.h>

using namespace RTC;

TEST(ch4tests, translation) {
  auto transform = Translation(5, -3, 2);
  auto p = Tuple::MakePoint(-3, 4, 5);

  EXPECT_EQ(*(transform * *p), *Tuple::MakePoint(2, 1, 7));

  auto inv = transform.Inv();
  EXPECT_EQ(*(inv * *p), *Tuple::MakePoint(-8, 7, 3));

  auto v = Tuple::MakeVector(-3, 4, 5);
  EXPECT_EQ(*(inv * *v), *v);
}

TEST(ch4tests, scaling) {
  auto transform = Scaling(2, 3, 4);
  auto p = Tuple::MakePoint(-4, 6, 8);

  EXPECT_EQ(*(transform * *p), *Tuple::MakePoint(-8, 18, 32));

  auto v = Tuple::MakeVector(-4, 6, 8);
  EXPECT_EQ(*(transform * *v), *Tuple::MakeVector(-8, 18, 32));

  auto reverse = transform.Inv();
  EXPECT_EQ(*(reverse * *v), *Tuple::MakeVector(-2, 2, 2));
}

TEST(ch4tests, reflection) {
  auto transform = Scaling(-1, 1, 1);
  auto p = Tuple::MakePoint(2, 3, 4);
  EXPECT_EQ(*(transform * *p), *Tuple::MakePoint(-2, 3, 4));
}

TEST(ch4tests, rotationX) {
  auto p = Tuple::MakePoint(0, 1, 0);

  auto half_quarter = RotationX(RTC::PI / 4);
  auto full_quarter = RotationX(RTC::PI / 2);

  EXPECT_EQ(*(half_quarter * *p), *Tuple::MakePoint(0, sqrt(2) / 2, sqrt(2) / 2));
  EXPECT_EQ(*(full_quarter * *p), *Tuple::MakePoint(0, 0, 1));

  auto half_quarter_back = half_quarter.Inv();
  EXPECT_EQ(*(half_quarter_back * *p), *Tuple::MakePoint(0, sqrt(2) / 2, -sqrt(2) / 2));
}

TEST(ch4tests, rotationY) {
  auto p = Tuple::MakePoint(0, 0, 1);

  auto half_quarter = RotationY(RTC::PI / 4);
  auto full_quarter = RotationY(RTC::PI / 2);

  EXPECT_EQ(*(half_quarter * *p), *Tuple::MakePoint(sqrt(2) / 2, 0, sqrt(2) / 2));
  EXPECT_EQ(*(full_quarter * *p), *Tuple::MakePoint(1, 0, 0));
}

TEST(ch4tests, rotationZ) {
  auto p = Tuple::MakePoint(0, 1, 0);

  auto half_quarter = RotationZ(RTC::PI / 4);
  auto full_quarter = RotationZ(RTC::PI / 2);

  EXPECT_EQ(*(half_quarter * *p), *Tuple::MakePoint(-sqrt(2) / 2, sqrt(2) / 2, 0));
  EXPECT_EQ(*(full_quarter * *p), *Tuple::MakePoint(-1, 0, 0));
}
