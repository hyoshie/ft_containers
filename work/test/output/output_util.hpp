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

#endif /* OUTPUT_UTIL_HPP */
