#include "Tuple.h"

#include <cmath>
#include <cstdlib>
#include <limits>
#include <stdexcept>

using namespace RTC;

Tuple::Tuple(double X, double Y, double Z, double W) : x(X), y(Y), z(Z), w(W) {
}

bool
RTC::CompareDoubles(double a, double b) {
  auto eps = 0.00001;
  if (std::abs(a - b) > eps)
    return false;
  return true;
}

std::unique_ptr<Tuple>
Tuple::MakeTuple(double X, double Y, double Z, double W) {
  return std::make_unique<Tuple>(X, Y, Z, W);
}

std::unique_ptr<Tuple>
Tuple::MakePoint(double X, double Y, double Z) {
  return std::make_unique<Tuple>(X, Y, Z, 1.0);
}

std::unique_ptr<Tuple>
Tuple::MakeVector(double X, double Y, double Z) {
  return std::make_unique<Tuple>(X, Y, Z, 0.0);
}

bool
Tuple::IsPoint() const {
  return CompareDoubles(w, 1.0);
}

bool
Tuple::IsVector() const {
  return CompareDoubles(w, 0.0);
}

Tuple
Tuple::operator+(const Tuple &t1) const {
  if (IsPoint() && t1.IsPoint()) {
    throw std::runtime_error("Cannot add two points.");
  }
  return Tuple(this->x + t1.GetX(), this->y + t1.GetY(), this->z + t1.GetZ(), this->IsPoint() + t1.IsPoint());
}

Tuple
Tuple::operator-(const Tuple &t1) const {
  return Tuple(this->x - t1.GetX(), this->y - t1.GetY(), this->z - t1.GetZ(), this->IsPoint() - t1.IsPoint());
}

bool
Tuple::operator==(const Tuple &t1) const {
  if (!CompareDoubles(GetX(), t1.GetX()) ||
      !CompareDoubles(GetY(), t1.GetY()) ||
      !CompareDoubles(GetZ(), t1.GetZ()) ||
      !CompareDoubles(GetW(), t1.GetW())) {
    return false;
  }

  return true;
}

Tuple
Tuple::operator*(const double d) const {
  return Tuple(GetX() * d, GetY() * d, GetZ() * d, GetW() * d);
}

Tuple
Tuple::operator*(const Tuple &other) const {
  return Tuple(GetX() * other.GetX(), GetY() * other.GetY(), GetZ() * other.GetZ(), GetW() * other.GetW());
}

Tuple
Tuple::operator/(const double d) const {
  return Tuple(GetX() / d, GetY() / d, GetZ() / d, GetW() / d);
}

double
Tuple::Magnitude() const {
  return std::sqrt(x * x + y * y + z * z);
}

Tuple
Tuple::Normalize() const {
  return Tuple(x / Magnitude(), y / Magnitude(), z / Magnitude(), w);
}

double
RTC::Dot(const Tuple &t1, const Tuple &t2) {
  return t1.GetX() * t2.GetX() +
         t1.GetY() * t2.GetY() +
         t1.GetZ() * t2.GetZ();
}

double
RTC::Dot(const std::unique_ptr<Tuple> &t1, const std::unique_ptr<Tuple> &t2) {
  return t1->GetX() * t2->GetX() +
         t1->GetY() * t2->GetY() +
         t1->GetZ() * t2->GetZ();
}

Tuple
RTC::Cross(const Tuple &a, const Tuple &b) {
  if (!a.IsVector() || !b.IsVector())
    throw std::runtime_error("Cross product only works on vectors.");

  return *Tuple::MakeVector(a.GetY() * b.GetZ() - a.GetZ() * b.GetY(),
                            a.GetZ() * b.GetX() - a.GetX() * b.GetZ(),
                            a.GetX() * b.GetY() - a.GetY() * b.GetX());
}

std::unique_ptr<Tuple>
RTC::Cross(const std::unique_ptr<Tuple> &a, const std::unique_ptr<Tuple> &b) {
  if (!a->IsVector() || !b->IsVector())
    throw std::runtime_error("Cross product only works on vectors.");

  auto T = Tuple::MakeVector(a->GetY() * b->GetZ() - a->GetZ() * b->GetY(),
                             a->GetZ() * b->GetX() - a->GetX() * b->GetZ(),
                             a->GetX() * b->GetY() - a->GetY() * b->GetX());

  return T;
}
