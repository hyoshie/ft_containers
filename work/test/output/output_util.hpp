#ifndef OUTPUT_UTIL_HPP
#define OUTPUT_UTIL_HPP

#include <iostream>
#include <utility>

#include "pair.hpp"

template < typename U >
void pout(U message) {
  static int no;
  std::cout << std::endl;
  std::cout << "--- [" << ++no << "]:" << message << " ---" << std::endl;
}

template < class T1, class T2 >
std::ostream& operator<<(std::ostream& ostream,
                         const std::pair< T1, T2 >& pair) {
  ostream << "(" << pair.first << ", " << pair.second << ")";
  return ostream;
}

template < class T1, class T2 >
std::ostream& operator<<(std::ostream& ostream,
                         const ft::pair< T1, T2 >& pair) {
  ostream << "(" << pair.first << ", " << pair.second << ")";
  return ostream;
}

template < typename Value >
void print_value(Value value) {
  std::cout << value << std::endl;
}

template < typename Iter >
void print_iter(Iter iter) {
  std::cout << *iter << std::endl;
}

template < typename Iter >
void print_iter_range(Iter first, Iter last) {
  for (; first != last; first++) {
    print_iter(first);
  }
}

template < typename Container >
void print_basic_info(Container c) {
  for (typename Container::const_iterator it = c.begin(); it != c.end(); it++) {
    print_value(*it);
  }
  std::cout << "size:" << c.size() << std::endl;
}

#endif /* OUTPUT_UTIL_HPP */
