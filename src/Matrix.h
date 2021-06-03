#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

using std::vector;

namespace RTC {
// clang-format off
constexpr double PI    = 3.14159265358979323846;
constexpr double PI_2  = 1.57079632679489661923;
constexpr double PI_4  = 0.78539816339744830962;
constexpr double SQRT2 = 1.41421356237309504880;
//clang-format on
class Tuple;

class Matrix {
 public:
  Matrix();
  Matrix(const std::vector<std::vector<double>>);
  Matrix(int);

  Matrix(const Matrix&);

  virtual ~Matrix() { };

  static Matrix Identity(size_t);

  vector<size_t> GetSize() const;
  void InsertRow(const vector<double>&);
  Matrix Transpose();
  Matrix& Inv();
  bool IsInvertable() const;
  double Det() const;
  double Minor(int, int) const;
  double Cofactor(int, int) const;
  void SetValue(size_t, size_t, double);

  const double& operator()(size_t, size_t) const;
  bool operator==(const Matrix&) const;
  Matrix& operator=(const Matrix&);
  Matrix operator*(const Matrix&) const;
  std::unique_ptr<Tuple> operator*(const Tuple&) const;
  virtual Matrix Submatrix(int, int) const;

 protected:
  vector<vector<double>> data;

private:
  std::unique_ptr<Matrix> inverse;
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

class Shearing : public Matrix {
 public:
  Shearing(double, double, double, double, double, double);
};

};  // namespace RTC
