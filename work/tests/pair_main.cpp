#include <sstream>
#include <vector>

#include "PairTester.hpp"

void test_pair() {
  std::vector< long > l_vector;
  for (int i = 0; i < 10; i++) {
    l_vector.push_back(i);
  }
  std::vector< std::string > str_vector;
  std::string base("test");
  for (int i = 0; i < 10; i++) {
    std::stringstream ss;
    ss << i;
    str_vector.push_back(base + ss.str());
  }
  PairTester< long, std::string, std::vector< long >,
              std::vector< std::string > >
      tester(l_vector, str_vector);
  tester.run();
}
