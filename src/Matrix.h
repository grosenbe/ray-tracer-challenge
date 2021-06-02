#include <cmath>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

using std::vector;

namespace RTC {

constexpr double PI = 3.14159265358979323846;

class Tuple;

class Matrix {
 public:
  Matrix() {}
  Matrix(const std::vector<std::vector<double>>);
  Matrix(int);

  static Matrix Identity(size_t);

  vector<size_t> GetSize() const;
  void InsertRow(const vector<double>&);
  Matrix Transpose();
  Matrix Inv() const;
  bool IsInvertable() const;
  double Det() const;
  double Minor(int, int) const;
  double Cofactor(int, int) const;

  double& operator()(size_t, size_t);
  const double& operator()(size_t, size_t) const;
  bool operator==(const Matrix&) const;
  Matrix operator*(const Matrix&) const;
  std::unique_ptr<Tuple> operator*(const Tuple&) const;
  virtual Matrix Submatrix(int, int) const;

 protected:
  vector<vector<double>> data;
};

class Translation : public Matrix {
 public:
  Translation(double, double, double);
};

class Scaling : public Matrix {
 public:
  Scaling(double, double, double);
};

class RotationX : public Matrix {
 public:
  RotationX(double);
};

class RotationY : public Matrix {
 public:
  RotationY(double);
};

class RotationZ : public Matrix {
 public:
  RotationZ(double);
};

};  // namespace RTC
