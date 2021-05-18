#ifndef TUPLE_H
#define TUPLE_H
#include <memory>
class Tuple {
 public:
  Tuple(double, double, double, double);

  double
  GetX() { return x; }

  double
  GetY() { return y; }

  double
  GetZ() { return z; }

  bool IsPoint();

  Tuple operator+(Tuple);
  Tuple operator-(Tuple);

 private:
  double x, y, z;
  bool w;
};

Tuple Point(double, double, double);
Tuple Vector(double, double, double);

bool CompareDoubles(double, double);
#endif
