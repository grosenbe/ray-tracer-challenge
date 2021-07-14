#include <iostream>

#include "src/Canvas.h"
#include "src/Tuple.h"

using namespace RTC;

int main(int, char **);

struct environment {
  RTC::Tuple gravity;
  RTC::Tuple wind;
};

struct projectile {
  RTC::Tuple position;
  RTC::Tuple velocity;

  void
  print() {
    std::cout << "Position: (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << ")" << std::endl;
  }
};

projectile
tick(environment &env, projectile &proj) {
  auto position = proj.position + proj.velocity;
  auto velocity = proj.velocity + env.gravity + env.wind;
  return projectile{position, velocity};
}

int
main(int argc __attribute__((unused)), char **argv __attribute__((unused))) {
  projectile p{RTC::Tuple::MakePoint(0, 1, 0), RTC::Tuple::MakeVector(1, 1, 0).Normalize()};

  environment e{RTC::Tuple::MakeVector(0, -0.1, 0), RTC::Tuple::MakeVector(0, 0, 0)};

  Canvas canvas(20, 20);

  while (p.position.GetY() > 0) {
    p = tick(e, p);
    canvas.WritePixel(p.position.GetX(), 19 - p.position.GetY(), Color(0, 1, 0));
  }

  canvas.CanvasToPPM("Projectile.ppm");
  return 0;
}
