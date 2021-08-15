#include "Camera.h"

#include <cmath>
#include <cstdint>

#include "World.h"

using namespace RTC;

Camera::Camera(uint32_t hSize, uint32_t vSize, double FOV) : hSize{hSize}, vSize{vSize}, FOV{FOV}, transform{Matrix::Identity(4)} {
  auto halfView = tan(FOV / 2);
  auto aspect = static_cast<double>(hSize) / vSize;

  if (aspect >= 1) {
    halfWidth = halfView;
    halfHeight = halfView / aspect;
  } else {
    halfWidth = halfView * aspect;
    halfHeight = halfView;
  }

  pixelSize = (halfWidth * 2) / hSize;
}

Ray
Camera::RayForPixel(int px, int py) {
  // offset from edge of canvas to pixel's center
  auto xOffset = (px + 0.5) * pixelSize;
  auto yOffset = (py + 0.5) * pixelSize;

  // untransformed coords of pixel in world space
  auto worldX = halfWidth - xOffset;
  auto worldY = halfHeight - yOffset;

  auto pixel = transform.Inv() * Tuple::MakePoint(worldX, worldY, -1);
  auto origin = transform.Inv() * Tuple::MakePoint(0, 0, 0);
  auto direction = (pixel - origin).Normalize();

  return Ray(origin, direction);
}

Canvas
Camera::Render(const World &world) {
  auto image = Canvas(hSize, vSize);

  for (auto y = 0u; y < vSize - 1; ++y) {
    for (auto x = 0u; x < hSize - 1; ++x) {
      auto ray = RayForPixel(x, y);
      image.WritePixel(x, y, color_at(world, ray));
    }
  }
  return image;
}
