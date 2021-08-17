#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>

#include "Canvas.h"
#include "Matrix.h"
#include "Ray.h"
#include "World.h"

#define NUM_THREADS 4

namespace RTC {

class Camera {
 public:
  Camera(uint32_t hSize, uint32_t vSize, double FOV);
  int
  getHSize() { return hSize; }
  int
  getVSize() { return vSize; }
  double
  getFOV() { return FOV; }
  const Matrix&
  getTransform() { return transform; }
  void
  setTransform(const Matrix& xfRm) { transform = xfRm; }
  double
  getPixelSize() { return pixelSize; }

  Ray RayForPixel(int, int);

  Canvas Render(const World&);

 private:
  uint32_t hSize, vSize;
  double FOV, pixelSize, halfWidth, halfHeight;
  Matrix transform;

  Canvas image;
  World world;
};
}  // namespace RTC
#endif
