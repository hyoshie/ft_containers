#include <algorithm>

#include "MapBenchmarkTester.hpp"

typedef NAMESPACE::pair< int, char > primitive_pair;

void test_map() {
  std::deque< primitive_pair > src1;
  for (int i = 0; i < MapBenchmarkTester< int, char >::kElemCount * 2; i += 2) {
    src1.push_back(primitive_pair(i, i % 95 + 32));
  }
  std::random_shuffle(src1.begin(), src1.end());

  std::deque< primitive_pair > src2;
  for (int i = 1; i < MapBenchmarkTester< int, char >::kElemCount * 2; i += 2) {
    src2.push_back(primitive_pair(i, i % 95 + 32));
  }
  std::random_shuffle(src2.begin(), src2.end());

  MapBenchmarkTester< int, char > tester(src1, src2);
  tester.run();
}
