#include <memory>

#include "src/Camera.h"
#include "src/Canvas.h"
#include "src/Material.h"
#include "src/Matrix.h"
#include "src/PointLight.h"
#include "src/World.h"

using namespace RTC;

int
main(void) {
  auto floor = sphere();
  floor->SetTransform(Scaling(10, 0.01, 10));
  floor->material.color = Color(1, 0.9, 0.9);
  floor->material.specular = 0;

  auto leftWall = sphere();
  leftWall->SetTransform(Translation(0, 0, 5) * RotationY(-PI_4) * RotationX(PI_2) * Scaling(10, 0.01, 10));
  leftWall->material = floor->material;

  auto rightWall = sphere();
  rightWall->SetTransform(Translation(0, 0, 5) * RotationY(PI_4) * RotationX(PI_2) * Scaling(10, 0.01, 10));
  rightWall->material = floor->material;

  auto middle = sphere();
  middle->SetTransform(Translation(-0.5, 1, 0.5));
  middle->material.color = Color(0.1, 1, 0.5);
  middle->material.diffuse = 0.7;
  middle->material.specular = 0.3;

  auto right = sphere();
  right->SetTransform(Translation(1.5, 0.5, -0.5) * Scaling(0.5, 0.5, 0.5));
  right->material.color = Color(0.5, 1, 0.1);
  right->material.diffuse = 0.7;
  right->material.specular = 0.3;

  auto left = sphere();
  left->SetTransform(Translation(-1.5, 0.33, -0.75) * Scaling(0.33, 0.33, 0.33));
  left->material.color = Color(1, 0.8, 0.1);
  left->material.diffuse = 0.7;
  left->material.specular = 0.3;

  World w;
  w.Light = std::make_shared<PointLight>(Tuple::MakePoint(-10, 10, -10), Color(1, 1, 1));
  w.Objects.push_back(floor);
  w.Objects.push_back(leftWall);
  w.Objects.push_back(rightWall);
  w.Objects.push_back(middle);
  w.Objects.push_back(right);
  w.Objects.push_back(left);

  Camera camera(1366, 768, PI / 3);
  camera.setTransform(view_transformation(Tuple::MakePoint(0, 1.5, -5),
                                          Tuple::MakePoint(0, 1, 0),
                                          Tuple::MakeVector(0, 1, 0)));

  Canvas canvas = camera.Render(w);
  canvas.CanvasToPPM("TestImage.ppm");
}
