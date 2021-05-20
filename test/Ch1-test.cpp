#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>

#include "src/Tuple.h"

TEST(ch1tests, construct_tuples) {
  auto A = Tuple::MakePoint(4.3, -4.2, 3.1);
  EXPECT_EQ(A->GetX(), 4.3);
  EXPECT_EQ(A->GetY(), -4.2);
  EXPECT_EQ(A->GetZ(), 3.1);
  EXPECT_TRUE(A->IsPoint());

  auto B = Tuple::MakeVector(4.3, -4.2, 3.1);
  EXPECT_EQ(B->GetX(), 4.3);
  EXPECT_EQ(B->GetY(), -4.2);
  EXPECT_EQ(B->GetZ(), 3.1);
  EXPECT_FALSE(B->IsPoint());
}

TEST(ch1tests, factory_functions) {
  auto p = Tuple::MakePoint(4, -4, 3);
  auto v = Tuple::MakeVector(4, -4, 3);

  EXPECT_EQ(p->GetX(), 4);
  EXPECT_EQ(p->GetY(), -4);
  EXPECT_EQ(p->GetZ(), 3);
  EXPECT_TRUE(p->IsPoint());

  EXPECT_EQ(v->GetX(), 4);
  EXPECT_EQ(v->GetY(), -4);
  EXPECT_EQ(v->GetZ(), 3);
  EXPECT_FALSE(v->IsPoint());
}

TEST(ch1tests, tuple_addition) {
  auto a1 = Tuple::MakePoint(3, -2, 5);
  auto a2 = Tuple::MakeVector(-2, 3, 1);

  auto a3 = *a1 + *a2;

  EXPECT_EQ(a3.GetX(), 1);
  EXPECT_EQ(a3.GetY(), 1);
  EXPECT_EQ(a3.GetZ(), 6);
  EXPECT_TRUE(a3.IsPoint());
}

TEST(ch1tests, tuple_subtraction) {
  auto p1 = Tuple::MakePoint(3, 2, 1);
  auto p2 = Tuple::MakePoint(5, 6, 7);

  EXPECT_EQ(*p1 - *p2, *Tuple::MakeVector(-2, -4, -6));

  auto v1 = Tuple::MakeVector(5, 6, 7);
  EXPECT_EQ(*p1 - *v1, *Tuple::MakePoint(-2, -4, -6));

  auto v2 = Tuple::MakeVector(3, 2, 1);
  EXPECT_EQ(*v2 - *v1, *Tuple::MakeVector(-2, -4, -6));
}

TEST(ch1tests, tuple_negation) {
  auto zero = Tuple::MakeVector(0, 0, 0);
  auto v = Tuple::MakeVector(1, -2, 3);

  EXPECT_EQ(*zero - *v, *Tuple::MakeVector(-1, 2, -3));
}

TEST(ch1tests, tuple_multiplication) {
  auto a = Tuple::MakeTuple(1, -2, 3, -4);

  EXPECT_EQ(*a * 3.5, *Tuple::MakeTuple(3.5, -7, 10.5, -14));
  EXPECT_EQ(*a * 0.5, *Tuple::MakeTuple(0.5, -1, 1.5, -2));
  EXPECT_EQ(*a / 2, *Tuple::MakeTuple(0.5, -1, 1.5, -2));
}

TEST(ch1tests, tuple_magnitude) {
  EXPECT_EQ(Tuple::MakeVector(1, 0, 0)->Magnitude(), 1);
  EXPECT_EQ(Tuple::MakeVector(0, 1, 0)->Magnitude(), 1);
  EXPECT_EQ(Tuple::MakeVector(1, 0, 0)->Magnitude(), 1);
  EXPECT_EQ(Tuple::MakeVector(0, 0, 1)->Magnitude(), 1);
  EXPECT_EQ(Tuple::MakeVector(1, 2, 3)->Magnitude(), std::sqrt(14));
  EXPECT_EQ(Tuple::MakeVector(-1, -2, -3)->Magnitude(), std::sqrt(14));
}

TEST(ch1tests, tuple_normalization) {
  EXPECT_EQ(Tuple::MakeVector(4, 0, 0)->Normalize(), *Tuple::MakeVector(1, 0, 0));
  EXPECT_EQ(Tuple::MakeVector(1, 2, 3)->Normalize(), *Tuple::MakeVector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14)));
}

TEST(ch1test, tuple_dotProduct) {
  auto a = Tuple::MakeVector(1, 2, 3);
  auto b = Tuple::MakeVector(2, 3, 4);

  EXPECT_EQ(Dot(*a, *b), 20);
}

TEST(ch1test, tuple_crossProduct) {
  auto a = Tuple::MakeVector(1, 2, 3);
  auto b = Tuple::MakeVector(2, 3, 4);

  EXPECT_EQ(Cross(*a, *b), *Tuple::MakeVector(-1, 2, -1));
  EXPECT_EQ(Cross(*b, *a), *Tuple::MakeVector(1, -2, 1));
}
