#include "Camera.h"

#include <cmath>
#include <cstdint>
#include <thread>

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

void
Camera::RenderSubimage(Canvas image, const World world, const std::pair<uint32_t, uint32_t> xExtents, const std::pair<uint32_t, uint32_t> yExtents) {
  for (auto y = yExtents.first; y < yExtents.second; ++y) {
    for (auto x = xExtents.first; x < xExtents.second; ++x) {
      auto ray = RayForPixel(x, y);
      image.WritePixel(x, y, color_at(world, ray));
    }
  }
}

Canvas
Camera::Render(const World &aWorld) {
  world = aWorld;
  image = Canvas(hSize, vSize);

  auto horizExtents = std::make_pair(0, hSize / 2 - 1);
  auto vertExtents = std::make_pair(0, vSize / 2 - 1);
  std::thread th1([&](std::pair<uint32_t, uint32_t> xExtents, std::pair<uint32_t, uint32_t> yExtents) {
    for (auto y = yExtents.first; y < yExtents.second; ++y) {
      for (auto x = xExtents.first; x < xExtents.second; ++x) {
        auto ray = RayForPixel(x, y);
        image.WritePixel(x, y, color_at(world, ray));
      }
    }
  },
                  horizExtents, vertExtents);

  auto horizExtents2 = std::make_pair(hSize / 2, hSize);
  auto vertExtents2 = std::make_pair(vSize / 2, vSize);
  std::thread th2([&](std::pair<uint32_t, uint32_t> xExtents, std::pair<uint32_t, uint32_t> yExtents) {
    for (auto y = yExtents.first; y < yExtents.second; ++y) {
      for (auto x = xExtents.first; x < xExtents.second; ++x) {
        auto ray = RayForPixel(x, y);
        image.WritePixel(x, y, color_at(world, ray));
      }
    }
  },
                  horizExtents2, vertExtents2);

  th1.join();
  th2.join();

  return image;
}
