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

  auto pixel = transform.Inverse() * Tuple::MakePoint(worldX, worldY, -1);
  auto origin = transform.Inverse() * Tuple::MakePoint(0, 0, 0);
  auto direction = (pixel - origin).Normalize();

  return Ray(origin, direction);
}

Canvas
Camera::Render(const World &aWorld) {
  world = aWorld;
  image = Canvas(hSize, vSize);
  transform.Inverse();
  std::vector<std::thread> threads;
  for (auto t = 0u; t < NUM_THREADS; ++t) {
    threads.emplace_back(std::thread([&](std::pair<uint32_t, uint32_t> xExtents, std::pair<uint32_t, uint32_t> yExtents) {
      for (auto y = yExtents.first; y <= yExtents.second; ++y) {
        for (auto x = xExtents.first; x < xExtents.second; ++x) {
          auto ray = RayForPixel(x, y);
          image.WritePixel(x, y, color_at(world, ray));
        }
      }
    },
                                     std::make_pair(0, hSize), std::make_pair(t * vSize / NUM_THREADS, (t + 1) * vSize / NUM_THREADS - 1)));
  }

  for (auto &t : threads)
    t.join();

  return image;
}
