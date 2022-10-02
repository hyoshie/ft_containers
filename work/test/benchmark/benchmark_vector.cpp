#include <algorithm>

#include "VectorBenchmarkTester.hpp"

void test_vector() {
  std::deque< int > src1;
  for (int i = 0; i < VectorBenchmarkTester< int >::kElemCount * 2; i += 2) {
    src1.push_back(i);
  }
  std::random_shuffle(src1.begin(), src1.end());

  VectorBenchmarkTester< int > tester(src1);
  tester.run();
}
