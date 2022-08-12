#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

template <typename T, std::size_t N>
struct array {
  using value_type = T;
  using reference = T &;
  using const_reference = T const &;
  using size_type = std::size_t;

  value_type storage[N];

  reference operator[](size_type i) { return storage[i]; }
  const_reference operator[](size_type i) const { return storage[i]; }
  size_type size() const;

  reference front() { return storage[0]; }
  const_reference front() const { return storage[0]; }
  reference back() { return storage[N - 1]; }
  const_reference back() const { return storage[N - 1]; }

  // array();
  // ~array();
  // array(const array &other);
  // array &operator=(const array &other);
};

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return N;
}

#endif /* ARRAY_HPP */
