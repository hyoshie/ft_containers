#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdlib>
#include <iterator>

template < typename Container >
typename Container::iterator random_itr(Container& c) {
  typename Container::iterator start = c.begin();
  std::advance(start, rand() % c.size());
  return (start);
}

template < typename Container >
typename Container::iterator random_itr(Container& c,
                                        typename Container::iterator start) {
  std::advance(start, rand() % std::distance(start, c.end()));
  return (start);
}

// template < typename Container >
// typename Container::iterator random_itr(
//     Container& c, typename Container::const_iterator start) {
//   std::advance(start, rand() % std::distance(start, c.end()));
//   return (start);
// }

#endif /* RANDOM_HPP */
