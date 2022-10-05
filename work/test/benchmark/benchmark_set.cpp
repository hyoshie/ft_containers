#include <algorithm>

#include "SetBenchmarkTester.hpp"

void test_set() {
  std::deque< int > src1;
  for (int i = 0; i < SetBenchmarkTester< int >::kElemCount * 2; i += 2) {
    src1.push_back(i);
  }
  std::random_shuffle(src1.begin(), src1.end());

  std::deque< int > src2;
  for (int i = 1; i < SetBenchmarkTester< int >::kElemCount * 2; i += 2) {
    src2.push_back(i);
  }
  std::random_shuffle(src2.begin(), src2.end());

  SetBenchmarkTester< int > tester(src1, src2);
  tester.run();
}
