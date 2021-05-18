#ifndef TUPLE_H
#define TUPLE_H
#include <memory>
class Tuple {
 public:
  Tuple(double, double, double, double);

  double
  GetX() const { return x; }

  double
  GetY() const { return y; }

  double
  GetZ() const { return z; }

  double
  GetW() const { return w; }

  bool
  IsPoint() const;

  Tuple operator+(const Tuple &) const;
  Tuple operator-(const Tuple &) const;

  bool operator==(const Tuple &) const;

  Tuple operator*(const double) const;
  Tuple operator/(const double) const;

  double Magnitude() const;

  Tuple Normalize() const;

 private:
  double x, y, z, w;
};

Tuple Point(double, double, double);
Tuple Vector(double, double, double);

double Dot(const Tuple &, const Tuple &);
Tuple Cross(const Tuple &, const Tuple &);

bool CompareDoubles(double, double);
#endif
