#include "Tuple.h"

#include <cstdlib>
#include <limits>

Tuple::Tuple(double X, double Y, double Z, double W) : x(X), y(Y), z(Z) {
  if (CompareDoubles(W, 1.0)) {
    w = true;
  } else {
    w = false;
  }
}

bool
Tuple::IsPoint() {
  return w;
}

bool
CompareDoubles(double a, double b) {
  if (std::abs(a - b) > std::numeric_limits<double>::epsilon())
    return false;
  return true;
}

Tuple Point(double X, double Y, double Z) {
  return Tuple(X, Y, Z, 1.0);
}

Tuple Vector(double X, double Y, double Z) {
  return Tuple(X, Y, Z, 0.0);
}

Tuple
Tuple::operator+(Tuple t1) {
  // TODO: handle if this is a point and we're adding another point
  return Tuple(this->x + t1.GetX(), this->y + t1.GetY(), this->z + t1.GetZ(), 0.0);
}

Tuple
Tuple::operator-(Tuple t1) {
  // TODO: handle if this is a point and we're adding another point
  
  return Tuple(this->x - t1.GetX(), this->y - t1.GetY(), this->z - t1.GetZ(), 0.0);
}
