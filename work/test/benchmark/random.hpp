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
typename Container::const_iterator random_itr(const Container& c) {
  typename Container::const_iterator start = c.begin();
  std::advance(start, rand() % c.size());
  return (start);
}

template < typename Container >
typename Container::iterator random_itr(Container& c,
                                        typename Container::iterator start) {
  std::advance(start, rand() % std::distance(start, c.end()));
  return (start);
}

template < typename Container >
typename Container::size_type random_index(const Container& c) {
  return rand() % c.size();
}

template < typename Container >
typename Container::size_type random_size(const Container& c) {
  typename Container::size_type size = rand() % c.size();
  return (size == 0) ? 1 : size;
}

size_t random_mini();

#endif /* RANDOM_HPP */
