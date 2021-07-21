#include "src/Canvas.h"
#include "src/Matrix.h"
#include "src/PointLight.h"
#include "src/Sphere.h"
#include "src/Tuple.h"

using namespace RTC;

int
main(void) {
  // Cast rays from a given point toward the canvas. Any ray that does not hit the sphere will cast
  // onto the canvas.
  auto ray_origin = Tuple::MakePoint(0, 0, -5);
  auto wall_size = 7.0;
  auto canvas_pixels = 100u;
  auto pixel_size = wall_size / canvas_pixels;
  auto half = wall_size / 2;
  auto wall_z = 10;

  Canvas canvas(canvas_pixels, canvas_pixels);
  Color color(1, 0, 0);
  auto shape = sphere();
  shape->material = Material();
  shape->material.color = Color(1, 0.2, 1);

  auto light = PointLight(Tuple::MakePoint(-10, 10, -10), Color(1, 1, 1));

  for (auto y = 0u; y < canvas_pixels; ++y) {
    auto world_y = half - pixel_size * y;
    for (auto x = 0u; x < canvas_pixels; ++x) {
      auto world_x = -half + pixel_size * x;
      auto position = Tuple::MakePoint(world_x, world_y, wall_z);
      auto r = Ray(ray_origin, (position - ray_origin).Normalize());
      auto xs = intersect(shape, r);
      if (xs.size() != 0) {
        auto point = Position(r, xs[0].t);
        auto normal = xs[0].object->normal_at(point);
        auto eye = Tuple::MakeVector(0, 0, 0) - r.direction;
        auto color = Lighting(xs[0].object->material, light, point, eye, normal);
        canvas.WritePixel(x, y, color);
      }
    }
  }

  canvas.CanvasToPPM("sphere.ppm");
}
