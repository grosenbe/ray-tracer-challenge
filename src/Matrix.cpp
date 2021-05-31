#include "Matrix.h"

#include <cmath>
#include <limits>
#include <stdexcept>

#include "Tuple.h"

using namespace RTC;

Matrix::Matrix(int Size) {
  if (Size < 0)
    throw std::runtime_error("Can't have a matrix with negative size");
  size_t size = Size;

  for (auto r = 0u; r < size; ++r) {
    auto row = std::vector<double>(size, 0);
    InsertRow(row);
  }
}

Matrix::Matrix(const std::vector<std::vector<double>> Data) {
  for (const auto& r : Data) {
    InsertRow(r);
  }
}

vector<size_t>
Matrix::GetSize() const {
  vector<size_t> ret{0, 0};
  ret[0] = data.size();
  if (ret[0] > 0)
    ret[1] = data[0].size();
  return ret;
}

void
Matrix::InsertRow(const vector<double>& newRow) {
  if (data.size() > 0 && newRow.size() != data[0].size()) {
    std::string errMsg = "Attempting to insert a new row of length " + std::to_string(newRow.size()) + " into a matrix whose rows are length " + std::to_string(data[0].size());
    throw std::runtime_error(errMsg);
  }

  data.push_back(newRow);
}

double&
Matrix::operator()(size_t Row, size_t Col) {
  if (Row >= data.size()) {
    throw std::runtime_error("Matrix only has " + std::to_string(data.size()) + " rows");
  }
  if (Col >= data[0].size()) {
    throw std::runtime_error("Matrix only has " + std::to_string(data[0].size()) + " columns");
  }
  return data[Row][Col];
}

const double&
Matrix::operator()(size_t Row, size_t Col) const {
  if (Row >= data.size()) {
    throw std::runtime_error("Matrix only has " + std::to_string(data.size()) + " rows");
  }
  if (Col >= data[0].size()) {
    throw std::runtime_error("Matrix only has " + std::to_string(data[0].size()) + " columns");
  }
  return data[Row][Col];
}

bool
Matrix::operator==(const Matrix& Other) const {
  auto mySize = GetSize();
  auto otherSize = Other.GetSize();

  if (mySize[0] != otherSize[0] || mySize[1] != otherSize[1])
    return false;

  for (auto r = 0u; r < mySize[0]; ++r) {
    for (auto c = 0u; c < mySize[1]; ++c) {
      if (!CompareDoubles((*this)(r, c), Other(r, c)))
        return false;
    }
  }
  return true;
}

Matrix
Matrix::operator*(const Matrix& other) const {
  auto mySize = GetSize();
  auto otherSize = other.GetSize();

  if (mySize[1] != otherSize[0])
    throw std::runtime_error("Number of columns of left matrix must equal number of rows of right matrix.");

  Matrix result;
  for (auto rRow = 0u; rRow < mySize[0]; ++rRow) {
    result.InsertRow(std::vector<double>(otherSize[1], std::numeric_limits<double>::quiet_NaN()));
    for (auto rCol = 0u; rCol < otherSize[1]; ++rCol) {
      result(rRow, rCol) = 0;
      for (auto m = 0u; m < otherSize[0]; ++m) {
        result(rRow, rCol) += data[rRow][m] * other(m, rCol);
      }
    }
  }
  return result;
}

std::unique_ptr<Tuple>
Matrix::operator*(const Tuple& Tuple) const {
  auto mySize = GetSize();
  if (mySize[0] != 4 || mySize[1] != 4) {
    throw std::runtime_error("Can only multiply 4x4 matricies by tuples");
  }

  return Tuple::MakeTuple(data[0][0] * Tuple.GetX() + data[0][1] * Tuple.GetY() + data[0][2] * Tuple.GetZ() + data[0][3] * Tuple.GetW(),
                          data[1][0] * Tuple.GetX() + data[1][1] * Tuple.GetY() + data[1][2] * Tuple.GetZ() + data[1][3] * Tuple.GetW(),
                          data[2][0] * Tuple.GetX() + data[2][1] * Tuple.GetY() + data[2][2] * Tuple.GetZ() + data[2][3] * Tuple.GetW(),
                          data[3][0] * Tuple.GetX() + data[3][1] * Tuple.GetY() + data[3][2] * Tuple.GetZ() + data[3][3] * Tuple.GetW());
}

Matrix
Matrix::Identity(size_t size) {
  Matrix result;
  for (auto r = 0u; r < size; ++r) {
    auto row = std::vector<double>(size, 0);
    row[r] = 1;
    result.InsertRow(row);
  }
  return result;
}

Matrix
Matrix::Transpose() {
  Matrix transposed;

  for (auto r = 0u; r != data.size(); ++r)
    transposed.InsertRow(std::vector<double>(data.size(), 0));

  for (auto r = 0u; r != data.size(); ++r) {
    for (auto c = 0u; c != data.size(); ++c) {
      transposed(r, c) = data[c][r];
    }
  }
  return transposed;
}

double
Matrix::Det() const {
  if (data[0].size() == 2)
    return data[0][0] * data[1][1] - data[0][1] * data[1][0];

  double det = 0;
  for (auto c = 0u; c < data[0].size(); ++c) {
    auto product = data[0][c] * Cofactor(0, c);
    det += product;
  }
  return det;
}

Matrix
Matrix::Submatrix(int Row, int Col) const {
  if (Row < 0 || Col < 0)
    throw std::runtime_error("Submatrix: Row and Col must be >= 0");
  auto RowU = static_cast<size_t>(Row);
  auto ColU = static_cast<size_t>(Col);

  Matrix sub;
  for (auto r = 0u; r < data.size(); ++r) {
    vector<double> row(data[0].size() - 1, 0);
    if (r == RowU)
      continue;

    auto colCount = 0u;
    for (auto c = 0u; c < data[0].size(); ++c) {
      if (c == ColU)
        continue;
      row[colCount++] = data[r][c];
    }
    sub.InsertRow(row);
  }
  return sub;
}

double
Matrix::Minor(int row, int col) const {
  return Submatrix(row, col).Det();
}

double
Matrix::Cofactor(int Row, int Col) const {
  if ((Row + Col) % 2) {
    return -Minor(Row, Col);
  } else {
    return Minor(Row, Col);
  }
}

bool
Matrix::IsInvertable() const {
  return Det() != 0;
}

Matrix
Matrix::Inv() const {
  if (!IsInvertable()) {
    throw std::runtime_error("Tried to take the inverse of a non-invertable matrix.");
  }
  Matrix M2(data.size());

  auto det = Det();
  for (auto row = 0u; row < data.size(); ++row) {
    for (auto col = 0u; col < data.size(); ++col) {
      M2(col, row) = Cofactor(row, col) / det;
    }
  }

  return M2;
}
