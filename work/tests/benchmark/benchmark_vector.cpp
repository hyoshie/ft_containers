#include <algorithm>

#include "VectorBenchmarkTester.hpp"

void test_vector() {
  std::deque< int > src1;
  for (int i = 0; i < 20; i += 2) {
    src1.push_back(i);
  }
  std::random_shuffle(src1.begin(), src1.end());

  VectorBenchmarkTester< int > tester(src1);
  tester.run();
  ;
  std::cerr << "[\x1b[32mPASS\x1b[39m]" << std::endl;
}