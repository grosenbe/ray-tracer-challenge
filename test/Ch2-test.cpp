#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "src/Canvas.h"
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

  EXPECT_EQ(C1 + C2, Color(1.6, 0.7, 1.0));
  EXPECT_EQ(C1 - C2, Color(0.2, 0.5, 0.5));

  auto c = Color(0.2, 0.3, 0.4);
  EXPECT_EQ(c * 2, Color(0.4, 0.6, 0.8));
}

TEST(ch2tests, hadamard) {
  auto c1 = Color(1, 0.2, 0.4);
  auto c2 = Color(0.9, 1, 0.1);

  EXPECT_EQ(c1 * c2, Color(0.9, 0.2, 0.04));
}

TEST(ch2tests, canvas) {
  auto C = Canvas(10, 20);
  EXPECT_EQ(C.Width(), 10);
  EXPECT_EQ(C.Height(), 20);

  for (auto r = 0u; r < C.Height(); ++r) {
    for (auto c = 0u; c < C.Width(); ++c) {
      EXPECT_EQ(C.Data(c, r), Color(0, 0, 0));
    }
  }
}

TEST(ch2tests, writeColor) {
  auto C = Canvas(10, 20);
  auto red = Color(1, 0, 0);

  C.WritePixel(2, 3, red);
  EXPECT_EQ(C.Data(2, 3), red);
  EXPECT_ANY_THROW(C.WritePixel(10, 20, red));
}

TEST(ch2tests, ppmHeader) {
  auto c = Canvas(5, 3);
  auto C1 = Color(1.5, 0, 0);
  auto C2 = Color(0, 0.5, 0);
  auto C3 = Color(-0.5, 0, 1);

  c.WritePixel(0, 0, C1);
  c.WritePixel(2, 1, C2);
  c.WritePixel(4, 2, C3);
  c.CanvasToPPM("test.ppm");

  std::ifstream input("test.ppm");
  std::string line;

  getline(input, line);
  EXPECT_EQ(line, "P3");

  getline(input, line);
  EXPECT_EQ(line, "5 3");

  getline(input, line);
  EXPECT_EQ(line, "255");

  getline(input, line);
  EXPECT_EQ(line, "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");

  getline(input, line);
  EXPECT_EQ(line, "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");

  getline(input, line);
  EXPECT_EQ(line, "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}
