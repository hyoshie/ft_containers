#include <iostream>

#include "Fixed.hpp"
#include "MapTester.hpp"

#if USE_STL
#define NAMESPACE std
#else
#define NAMESPACE ft
#endif

#include <algorithm>
#include <deque>

typedef NAMESPACE::pair< int, char > pair_ic_t;
typedef NAMESPACE::pair< Fixed, short > pair_fs_t;

void test_int_char() {
  int elem_count = MapTester< int, char >::kElemCount;

  std::deque< pair_ic_t > src1;
  for (int i = 0; i < elem_count * 2; i += 2) {
    src1.push_back(pair_ic_t(i, i % 95 + 32));
  }
  std::random_shuffle(src1.begin(), src1.end());

  std::deque< pair_ic_t > src2;
  for (int i = 1; i < elem_count * 2; i += 2) {
    src2.push_back(pair_ic_t(i, i % 95 + 32));
  }
  std::random_shuffle(src2.begin(), src2.end());

  pair_ic_t min_pair(-1, 'X');
  MapTester< int, char > primitive_tester(src1, src2, min_pair);
  primitive_tester.run();
}

void test_fixed_short() {
  int elem_count = MapTester< Fixed, short >::kElemCount;

  std::deque< pair_fs_t > src1;
  float base = 1.5;
  for (int i = 0; i < elem_count * 2; i += 2) {
    src1.push_back(pair_fs_t(Fixed(base * i), i));
  }
  std::random_shuffle(src1.begin(), src1.end());

  std::deque< pair_fs_t > src2;
  for (int i = 1; i < elem_count * 2; i += 2) {
    src2.push_back(pair_fs_t(Fixed(base * i), i));
  }
  std::random_shuffle(src2.begin(), src2.end());

  pair_fs_t min_pair(Fixed(base * -1), 'X');
  MapTester< Fixed, short > primitive_tester(src1, src2, min_pair);
  primitive_tester.run();
}

static void test_primitive() {
  test_int_char();
  ;
}

static void test_user_defined() {
  test_fixed_short();
  ;
}

void test_map() {
  srand(time(NULL));
  test_primitive();
  test_user_defined();
}
