#include <iostream>

#include "src/Tuple.h"

int main(int, char **);

struct environment {
  Tuple gravity;
  Tuple wind;
};

struct projectile {
  Tuple position;
  Tuple velocity;

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
  projectile p{*Tuple::MakePoint(0, 1, 0), Tuple::MakeVector(1, 1, 0)->Normalize()};

  environment e{*Tuple::MakeVector(0, -0.1, 0), *Tuple::MakeVector(-0.01, 0, 0)};

  while (p.position.GetY() > 0) {
    p = tick(e, p);
    p.print();
  }
  return 0;
}
