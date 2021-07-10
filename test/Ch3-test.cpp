#include <gtest/gtest.h>

#include <stdexcept>

#include "src/Matrix.h"
#include "src/Tuple.h"

using namespace RTC;

using std::vector;

TEST(ch3tests, matricies) {
  Matrix M, M2, M3;
  M.InsertRow({1, 2, 3, 4});
  M.InsertRow({5.5, 6.5, 7.5, 8.5});
  M.InsertRow({9, 10, 11, 12});
  M.InsertRow({13.5, 14.5, 15.5, 16.5});
  EXPECT_ANY_THROW(M.InsertRow({9, 10, 11, 12, 13}));
  EXPECT_EQ(M(0, 0), 1);
  EXPECT_EQ(M(0, 3), 4);
  EXPECT_EQ(M(1, 0), 5.5);
  EXPECT_EQ(M(1, 2), 7.5);
  EXPECT_EQ(M(2, 2), 11);
  EXPECT_EQ(M(3, 0), 13.5);
  EXPECT_EQ(M(3, 2), 15.5);
  EXPECT_ANY_THROW(M(10, 10));

  M.SetValue(3, 0, 13.2);
  EXPECT_EQ(M(3, 0), 13.2);

  M2.InsertRow({-3, 5});
  M2.InsertRow({1, -2});
  EXPECT_EQ(M2(0, 0), -3);
  EXPECT_EQ(M2(0, 1), 5);
  EXPECT_EQ(M2(1, 0), 1);
  EXPECT_EQ(M2(1, 1), -2);

  M3.InsertRow({-3, 5, 0});
  M3.InsertRow({1, 2, -7});
  M3.InsertRow({0, 1, 1});
  EXPECT_EQ(M3(0, 0), -3);
  EXPECT_EQ(M3(1, 0), 1);
  EXPECT_EQ(M3(2, 0), 0);
  EXPECT_EQ(M3(2, 2), 1);
  EXPECT_EQ(M3(1, 2), -7);

  EXPECT_EQ(M3.GetSize(), (vector<size_t>{3, 3}));
}

TEST(ch3tests, equality) {
  Matrix M, M2, M3;
  M.InsertRow({1, 2, 3, 4});
  M.InsertRow({5.5, 6.5, 7.5, 8.5});
  M.InsertRow({9, 10, 11, 12});
  M.InsertRow({13.5, 14.5, 15.5, 16.5});

  M2.InsertRow({1, 2, 3, 4});
  M2.InsertRow({5.5, 6.5, 7.5, 8.5});
  M2.InsertRow({9, 10, 11, 12});
  M2.InsertRow({13.5, 14.5, 15.5, 16.5});

  M3.InsertRow({1, 2, 3, 4});
  M3.InsertRow({5.5, 6.5, 7.5, 8.5});
  M3.InsertRow({9, 10, 11, 12});
  M3.InsertRow({13.5, 14.5, 15.5, 16.6});

  EXPECT_TRUE(M == M2);
  EXPECT_FALSE(M == M3);
}

TEST(ch3tests, multiplication) {
  Matrix M, M2, Product, M3;
  M.InsertRow({1, 2, 3, 4});
  M.InsertRow({5, 6, 7, 8});
  M.InsertRow({9, 8, 7, 6});
  M.InsertRow({5, 4, 3, 2});

  M2.InsertRow({-2, 1, 2, 3});
  M2.InsertRow({3, 2, 1, -1});
  M2.InsertRow({4, 3, 6, 5});
  M2.InsertRow({1, 2, 7, 8});

  Product.InsertRow({20, 22, 50, 48});
  Product.InsertRow({44, 54, 114, 108});
  Product.InsertRow({40, 58, 110, 102});
  Product.InsertRow({16, 26, 46, 42});

  M3.InsertRow({-2, 1, 2});
  M3.InsertRow({3, 2, 1});
  M3.InsertRow({4, 3, 6});

  EXPECT_EQ(Product, M * M2);
  EXPECT_ANY_THROW(M * M3);
}

TEST(ch3tests, tupleMultiplication) {
  Matrix M;
  M.InsertRow({1, 2, 3, 4});
  M.InsertRow({2, 4, 4, 2});
  M.InsertRow({8, 6, 4, 1});
  M.InsertRow({0, 0, 0, 1});

  auto T = Tuple::MakeTuple(1, 2, 3, 1);
  auto expected = Tuple::MakeTuple(18, 24, 33, 1);
  auto product = M * T;

  EXPECT_EQ(product, expected);
}

TEST(ch3tests, identityMatrix) {
  Matrix eye;
  eye.InsertRow({1, 0, 0});
  eye.InsertRow({0, 1, 0});
  eye.InsertRow({0, 0, 1});
  EXPECT_EQ(eye, Matrix::Identity(3));

  Matrix A;
  A.InsertRow({0, 1, 2, 4});
  A.InsertRow({1, 2, 4, 8});
  A.InsertRow({2, 4, 8, 16});
  A.InsertRow({4, 8, 16, 32});

  EXPECT_EQ(A, A * Matrix::Identity(4));
  auto T = Tuple::MakeTuple(1, 2, 3, 4);
  EXPECT_EQ(T, Matrix::Identity(4) * T);
}

TEST(ch3tests, transpose) {
  Matrix M, MTranspose;
  M.InsertRow({0, 9, 3, 0});
  M.InsertRow({9, 8, 0, 8});
  M.InsertRow({1, 8, 5, 3});
  M.InsertRow({0, 0, 5, 8});

  MTranspose.InsertRow({0, 9, 1, 0});
  MTranspose.InsertRow({9, 8, 8, 0});
  MTranspose.InsertRow({3, 0, 5, 5});
  MTranspose.InsertRow({0, 8, 3, 8});
  EXPECT_EQ(M.Transpose(), MTranspose);

  Matrix eye = Matrix::Identity(3);
  EXPECT_EQ(eye.Transpose(), Matrix::Identity(3));
}

TEST(ch3tests, determinant_2x2) {
  Matrix M;
  M.InsertRow({1, 5});
  M.InsertRow({-3, 2});

  EXPECT_EQ(M.Det(), 17);
}

TEST(ch3tests, submatrix) {
  Matrix M1, sub1, M2, sub2;
  M1.InsertRow({1, 5, 0});
  M1.InsertRow({-3, 2, 7});
  M1.InsertRow({0, 6, -3});

  sub1.InsertRow({-3, 2});
  sub1.InsertRow({0, 6});
  EXPECT_EQ(M1.Submatrix(0, 2), sub1);

  M2.InsertRow({-6, 1, 1, 6});
  M2.InsertRow({-8, 5, 8, 6});
  M2.InsertRow({-1, 0, 8, 2});
  M2.InsertRow({-7, 1, -1, 1});

  sub2.InsertRow({-6, 1, 6});
  sub2.InsertRow({-8, 8, 6});
  sub2.InsertRow({-7, -1, 1});

  EXPECT_EQ(M2.Submatrix(2, 1), sub2);

  EXPECT_THROW(M2.Submatrix(-1, 0), std::runtime_error);
}

TEST(ch3tests, minor) {
  Matrix A({{3, 5, 0}, {2, -1, -7}, {6, -2, 5}});
  auto B = A.Submatrix(1, 0);

  EXPECT_EQ(B.Det(), 25);
  EXPECT_EQ(A.Minor(1, 0), 25);
}

TEST(ch3tests, cofactor) {
  Matrix M({{3, 5, 0}, {2, -1, -7}, {6, -1, 5}});

  EXPECT_EQ(M.Minor(0, 0), -12);
  EXPECT_EQ(M.Cofactor(0, 0), -12);
  EXPECT_EQ(M.Minor(1, 0), 25);
  EXPECT_EQ(M.Cofactor(1, 0), -25);
}

TEST(ch3tests, largerDeterminants) {
  Matrix A({{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}});
  EXPECT_EQ(A.Cofactor(0, 0), 56);
  EXPECT_EQ(A.Cofactor(0, 1), 12);
  EXPECT_EQ(A.Cofactor(0, 2), -46);
  EXPECT_EQ(A.Det(), -196);

  Matrix M({{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}});
  EXPECT_EQ(M.Cofactor(0, 0), 690);
  EXPECT_EQ(M.Cofactor(0, 1), 447);
  EXPECT_EQ(M.Cofactor(0, 2), 210);
  EXPECT_EQ(M.Cofactor(0, 3), 51);
  EXPECT_EQ(M.Det(), -4071);
}

TEST(ch3tests, isInvertable) {
  Matrix A({{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}});
  EXPECT_EQ(A.Det(), -2120);
  EXPECT_TRUE(A.IsInvertable());

  Matrix B({{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}});
  EXPECT_EQ(B.Det(), 0);
  EXPECT_FALSE(B.IsInvertable());
}

TEST(ch3tests, calculateInverse) {
  Matrix A({{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}});

  auto APrime = A.Inv();
  EXPECT_EQ(A.Det(), 532);
  EXPECT_EQ(A.Cofactor(2, 3), -160);
  EXPECT_EQ(APrime(3, 2), -160 / 532.);
  EXPECT_EQ(A.Cofactor(3, 2), 105);
  EXPECT_EQ(APrime(2, 3), 105 / 532.);

  Matrix APrimeExpected({{.21805, .45113, .24060, -0.04511},
                         {-.80827, -1.45677, -.44361, .52068},
                         {-.07895, -.22368, -.05263, .19737},
                         {-.52256, -.81391, -.30075, .30639}});
  EXPECT_EQ(APrime, APrimeExpected);

  Matrix B({{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}});
  auto BPrime = B.Inv();
  Matrix BPrimeExpected({{-.15385, -.15385, -.28205, -.53846},
                         {-.07692, .12308, .02564, .03077},
                         {.35897, .35897, .43590, .92308},
                         {-.69231, -.69231, -.76923, -1.92308}});
  EXPECT_EQ(BPrime, BPrimeExpected);

  Matrix C({{9, 3, 0, 9},
            {-5, -2, -6, -3},
            {-4, 9, 6, 4},
            {-7, 6, 6, 2}});
  auto CPrime = C.Inv();
  Matrix CPrimeExpected({{-.04074, -.07778, .14444, -.22222},
                         {-.07778, .03333, .36667, -.33333},
                         {-.02901, -.14630, -.10926, .12963},
                         {.17778, .06667, -.26667, .33333}});
  EXPECT_EQ(CPrime, CPrimeExpected);

  Matrix D({{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}});
  EXPECT_ANY_THROW(D.Inv());

  Matrix E({{3, -9, 7, 3},
            {3, -8, 2, -9},
            {-4, 4, 4, 1},
            {-6, 5, -1, 1}});
  Matrix F({{8, 2, 2, 2},
            {3, -1, 7, 0},
            {7, 0, 5, 4},
            {6, -2, 0, 5}});
  Matrix G = E * F;
  EXPECT_EQ(G * F.Inv(), E);
}
