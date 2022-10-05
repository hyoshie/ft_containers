#include <deque>

#include "Fixed.hpp"
#include "VectorTester.hpp"

static void test_int() {
  std::deque< int > int_deq;
  int elem_count = VectorTester< int >::kElemCount;
  for (int i = 0; i < elem_count; i++) {
    int_deq.push_back(i);
  }

  VectorTester< int > vec_tester(int_deq);
  vec_tester.run();
}

static void test_fixed() {
  std::deque< Fixed > fixed_deque;
  float base = 1.5;
  int elem_count = VectorTester< Fixed >::kElemCount;
  for (int i = 0; i < elem_count; i++) {
    fixed_deque.push_back(Fixed(base * i));
  }

  VectorTester< Fixed > fixed_tester(fixed_deque);
  fixed_tester.run();
}

static void test_primitive() {
  test_int();
  ;
}

static void test_user_defined() {
  test_fixed();
  ;
}

void test_vector() {
  test_primitive();
  test_user_defined();
}
