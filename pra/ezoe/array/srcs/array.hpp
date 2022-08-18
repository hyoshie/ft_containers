#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>

template <typename Array>
struct array_iterator;

template <typename T, std::size_t N>
struct array {
  using value_type = T;
  using reference = T &;
  using const_reference = T const &;
  using size_type = std::size_t;
  using iterator = array_iterator<array>;

  value_type storage[N];

  reference operator[](size_type i) { return storage[i]; }
  const_reference operator[](size_type i) const { return storage[i]; }
  size_type size() const { return N; };

  reference front() { return storage[0]; }
  const_reference front() const { return storage[0]; }
  reference back() { return storage[N - 1]; }
  const_reference back() const { return storage[N - 1]; }

  iterator begin() { return array_iterator<array>(*this, 0); }
  iterator end() { return array_iterator<array>(*this, N); }

  // array();
  // ~array();
  // array(const array &other);
  // array &operator=(const array &other);
};

template <typename Array>
struct array_iterator {
  Array &a_;
  std::size_t i_;

  array_iterator(Array &a, std::size_t i) : a_(a), i_(i){};

  array_iterator &operator++() {
    ++i_;
    return *this;
  };
  array_iterator &operator--() {
    --i_;
    return *this;
  };
  typename Array::reference operator*() { return a_[i_]; };
};

#endif /* ARRAY_HPP */
