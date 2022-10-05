#include <iostream>

#include "Fixed.hpp"
#include "SetTester.hpp"

#if USE_STL
#define NAMESPACE std
#else
#define NAMESPACE ft
#endif

#include <algorithm>
#include <deque>

void test_int() {
  int elem_count = SetTester< int >::kElemCount;

  std::deque< int > src1;
  for (int i = 0; i < elem_count * 2; i += 2) {
    src1.push_back(i);
  }
  std::random_shuffle(src1.begin(), src1.end());

  std::deque< int > src2;
  for (int i = 1; i < elem_count * 2; i += 2) {
    src2.push_back(i);
  }
  std::random_shuffle(src2.begin(), src2.end());

  int min = -1;
  SetTester< int > primitive_tester(src1, src2, min);
  primitive_tester.run();
}

// void test_fixed() {
//   int elem_count = SetTester< Fixed, short >::kElemCount;

//   std::deque< pair_fs_t > src1;
//   float base = 1.5;
//   for (int i = 0; i < elem_count * 2; i += 2) {
//     src1.push_back(pair_fs_t(Fixed(base * i), i));
//   }
//   std::random_shuffle(src1.begin(), src1.end());

//   std::deque< pair_fs_t > src2;
//   for (int i = 1; i < elem_count * 2; i += 2) {
//     src1.push_back(pair_fs_t(Fixed(base * i), i));
//   }
//   std::random_shuffle(src2.begin(), src2.end());

//   pair_fs_t min_pair(Fixed(base * -1), 'X');
//   SetTester< Fixed, short > primitive_tester(src1, src2, min_pair);
//   primitive_tester.run();
// }

static void test_primitive() {
  test_int();
  ;
}

// static void test_user_defined() {
//   // test_fixed();
//   ;
// }

void test_set() {
  srand(time(NULL));
  test_primitive();
  // test_user_defined();
}
