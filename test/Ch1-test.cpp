#include <gtest/gtest.h>

#include "src/Tuple.h"

TEST(ch1tests, construct_tuples) {
  Tuple A(4.3, -4.2, 3.1, 1.0);
  EXPECT_EQ(A.GetX(), 4.3);
  EXPECT_EQ(A.GetY(), -4.2);
  EXPECT_EQ(A.GetZ(), 3.1);
  EXPECT_TRUE(A.IsPoint());

  Tuple B(4.3, -4.2, 3.1, 0.0);
  EXPECT_EQ(B.GetX(), 4.3);
  EXPECT_EQ(B.GetY(), -4.2);
  EXPECT_EQ(B.GetZ(), 3.1);
  EXPECT_FALSE(B.IsPoint());
}

TEST(ch1tests, factory_functions) {
  auto p = Point(4, -4, 3);
  auto v = Vector(4, -4, 3);

  EXPECT_EQ(p.GetX(), 4);
  EXPECT_EQ(p.GetY(), -4);
  EXPECT_EQ(p.GetZ(), 3);
  EXPECT_TRUE(p.IsPoint());

  EXPECT_EQ(v.GetX(), 4);
  EXPECT_EQ(v.GetY(), -4);
  EXPECT_EQ(v.GetZ(), 3);
  EXPECT_FALSE(v.IsPoint());
}

TEST(ch1tests, tuple_addition) {
  auto v1 = Vector(1, 2, 3);
  auto v2 = Vector(1, 2, 3);

  auto v3 = v1 + v2;

  EXPECT_EQ(v3.GetX(), 2);
  EXPECT_EQ(v3.GetY(), 4);
  EXPECT_EQ(v3.GetZ(), 6);
  EXPECT_FALSE(v3.IsPoint());
}

TEST(ch1tests, tuple_subtraction) {
  auto p1 = Point(3, 2, 1);
  auto p2 = Point(5, 6, 7);

  auto v3 = p1 - p2;

  EXPECT_EQ(v3.GetX(), -2);
  EXPECT_EQ(v3.GetY(), -4);
  EXPECT_EQ(v3.GetZ(), -6);
  EXPECT_FALSE(v3.IsPoint());
}
