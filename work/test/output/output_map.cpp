#include <iostream>

#include "MapTester.hpp"

#if USE_STL
#define NAMESPACE std
#else
#define NAMESPACE ft
#endif

#include <algorithm>
#include <deque>

typedef NAMESPACE::pair< char, int > primitive_pair;

void test_primitive() {
  std::deque< primitive_pair > src1;
  for (int i = 0; i < 20; i += 2) {
    src1.push_back(primitive_pair('A' + i, 65 + i));
  }
  std::random_shuffle(src1.begin(), src1.end());

  std::deque< primitive_pair > src2;
  for (int i = 0; i < 26; i += 1) {
    src2.push_back(primitive_pair('A' + i, 65 + i));
  }
  std::random_shuffle(src2.begin(), src2.end());

  primitive_pair new_pair('B', 66);
  MapTester< char, int > primitive_tester(src1, src2, new_pair);
  primitive_tester.run();
}

void test_map() {
  srand(time(NULL));
  test_primitive();
  ;
}
