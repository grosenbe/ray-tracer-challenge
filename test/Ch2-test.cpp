#include <gtest/gtest.h>

#include "src/Color.h"

using namespace RTC;

TEST(ch2tests, colors) {
  auto C = Color(-0.5, 0.4, 1.7);

  EXPECT_EQ(C.red(), -0.5);
  EXPECT_EQ(C.green(), 0.4);
  EXPECT_EQ(C.blue(), 1.7);
}

TEST(ch2tests, colors_arithmetic) {
  auto C1 = Color(0.9, 0.6, 0.75);
  auto C2 = Color(0.7, 0.1, 0.25);

  EXPECT_TRUE(C1 + C2 == Color(1.6, 0.7, 1.0));
  EXPECT_TRUE(C1 - C2 == Color(0.2, 0.5, 0.5));

  auto c = Color(0.2, 0.3, 0.4);
  EXPECT_TRUE(c * 2 == Color(0.4, 0.6, 0.8));
}

TEST(ch2tests, hadamard) {
  auto c1 = Color(1, 0.2, 0.4);
  auto c2 = Color(0.9, 1, 0.1);

  EXPECT_TRUE(c1 * c2 == Color(0.9, 0.2, 0.04));
}
