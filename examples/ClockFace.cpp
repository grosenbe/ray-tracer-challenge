#include <iostream>

#include "src/Canvas.h"
#include "src/Matrix.h"
#include "src/Tuple.h"

// draw a simple clock face; IE, this is a [0, 1, 0] point, rotated about z by -i/12 * 2 * pi, where
// we just increment i
using namespace RTC;
int
main(void) {
  auto clockSize = 600;
  auto scaleFactor = clockSize / 2;
  auto hand = Tuple::MakePoint(0, 1, 0);

  auto canvas = Canvas(clockSize + 1, clockSize + 1);

  auto clockAngle = 1. / 12 * 2 * PI;
  double angle = 0;
  for (auto i = 0; i < 12; ++i) {
    auto xform = Scaling(scaleFactor, scaleFactor, 0) *
                 RotationZ(angle);
    auto position = xform * hand;
    std::cerr << "x: " << std::to_string(position.GetX()) << " y: " << std::to_string(position.GetY()) << std::endl;
    canvas.WritePixel(scaleFactor + position.GetX(), scaleFactor - position.GetY(), Color(1, 1, 1));
    angle -= clockAngle;
  }

  canvas.CanvasToPPM("Clock.ppm");
  return 0;
}
