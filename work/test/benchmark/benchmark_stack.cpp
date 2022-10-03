#include <algorithm>

#include "StackBenchmarkTester.hpp"
#include "vector.hpp"

void test_stack() {
  ft::vector< int > src1;
  for (int i = 0;
       i < StackBenchmarkTester< int, ft::vector< int > >::kElemCount * 2;
       i += 2) {
    src1.push_back(i);
  }
  std::random_shuffle(src1.begin(), src1.end());

  StackBenchmarkTester< int, ft::vector< int > > tester(src1);
  tester.run();
}
