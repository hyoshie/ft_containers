#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

#include "ezoe_iterator.hpp"
#include "iterator.hpp"
#include "util.hpp"

int main() {
  {
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    std::vector<int> v(5);
    std::copy(std::begin(a), std::end(a), std::begin(v));
    print(v);
  }
  {
    std::vector<int> v = {1, 2, 3, 4, 5};
    cout_iterator out;
    std::copy(std::begin(v), std::end(v), out);
    std::cout << std::endl;
  }
  {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::ostream_iterator<int> out(std::cout);
    std::copy(std::begin(v), std::end(v), out);
    std::cout << std::endl;
  }
  {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> tmp;
    auto out = back_inserter<std::vector<int>>(tmp);
    std::copy(std::begin(v), std::end(v), out);
    print(tmp);
  }
  {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> tmp;
    auto out = std::back_inserter(tmp);
    std::copy(std::begin(v), std::end(v), out);
    print(tmp);
  }
  // {
  //   cin_iterator<int> input, fail(true);
  //   std::vector<int> buffer;
  //   auto out = std::back_inserter(buffer);
  //   std::copy(input, fail, out);
  //   print(buffer);
  // }
  {
    std::vector<int> v = {1, 2, 3, 4, 5};
    print(std::begin(v), std::end(v));
  }
  // {
  //   cin_iterator<int> iter, fail(true);
  //   print(iter, fail);
  // }
  // {
  //   std::istream_iterator<int> iter(std::cin), end_iter;
  //   print(iter, end_iter);
  // }
  {
    iota_iterator<int> i;
    iota_iterator<int> first(0), last(10);

    i = last;
  }
  {
    iota_iterator<int> non_const(0);
    int value = *non_const;
    *non_const = 1;

    const iota_iterator<int> immutable(0);
    int const_value = *immutable;
    (void)const_value;
    (void)value;
  }
  {
    iota_iterator<int> first(0), last(10);

    first++;
    last--;
    std::cerr << *first << std::endl;
    std::cerr << *last << std::endl;
    ++first;
    --last;
    std::cerr << *first << std::endl;
    std::cerr << *last << std::endl;
  }
  {
    std::vector<int> v;
    for (int i = 0; i < 10; i++) {
      v.push_back(i);
    }
    std::vector<int> copy(v);
    std::cout << std::boolalpha << std::equal(v.begin(), v.end(), copy.begin())
              << std::endl;
  }
  {
    std::vector<int> v;
    std::vector<int> squared;
    for (int i = 0; i < 10; i++) {
      v.push_back(i);
      squared.push_back(i + 1);
    }
    std::cout << std::boolalpha
              << std::equal(v.begin(), v.end(), squared.begin(),
                            std::less<int>())
              << std::endl;
  }
}
