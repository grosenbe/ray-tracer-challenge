#ifndef TUPLE_H
#define TUPLE_H
#include <memory>
namespace RTC {
class Tuple {
 public:
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

  bool
  IsVector() const;

  Tuple operator+(const Tuple &) const;
  Tuple operator-(const Tuple &) const;

  bool operator==(const Tuple &) const;

  Tuple operator*(const double) const;
  Tuple operator*(const Tuple &) const;
  Tuple operator/(const double) const;

  double Magnitude() const;

  Tuple Normalize() const;

  static Tuple MakeVector(double, double, double);
  static Tuple MakePoint(double, double, double);
  static Tuple MakeTuple(double, double, double, double);

 private:
  double x, y, z, w;

 protected:
  Tuple(double, double, double, double);
};

double Dot(const Tuple &, const Tuple &);
Tuple Cross(const Tuple &, const Tuple &);

bool CompareDoubles(double, double);
}  // namespace RTC
#endif
