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

  // increment & decrement
  array_iterator &operator++() {
    ++i_;
    return *this;
  }
  array_iterator operator++(int) {
    array_iterator copy = *this;
    ++*this;
    return copy;
  }
  array_iterator &operator--() {
    --i_;
    return *this;
  }
  array_iterator operator--(int) {
    array_iterator copy = *this;
    --*this;
    return copy;
  }
  // comparsion
  // 写経したけどa_も同じオブジェクトか調べたほうがいい?
  bool operator==(array_iterator const &right) { return i_ == right.i_; }
  bool operator!=(array_iterator const &right) { return i_ != right.i_; }
  bool operator>(array_iterator const &right) { return i_ > right.i_; }
  bool operator>=(array_iterator const &right) {
    return *this == right || *this > right;
  }
  bool operator<(array_iterator const &right) { return i_ < right.i_; }
  bool operator<=(array_iterator const &right) {
    return *this == right || *this < right;
  }
  // alithmetic
  array_iterator &operator+=(std::size_t n) {
    i_ += n;
    return *this;
  }
  array_iterator operator+(std::size_t n) const {
    auto copy = *this;
    copy += n;
    return copy;
  }
  array_iterator &operator-=(std::size_t n) {
    i_ -= n;
    return *this;
  }
  array_iterator operator-(std::size_t n) const {
    auto copy = *this;
    copy -= n;
    return copy;
  }
  // subscript
  typename Array::reference operator[](std::size_t n) const {
    return *(*this + n);
  }
  typename Array::reference operator*() { return a_[i_]; };
};

template <typename Array>
struct array_const_iterator {
  Array &a_;
  std::size_t i_;

  array_const_iterator(Array &a, std::size_t i) : a_(a), i_(i){};
  array_const_iterator(typename array_iterator<Array>::iterator const &iter)
      : a_(iter.a_), i_(iter.i_){};

  // increment & decrement
  array_const_iterator &operator++() {
    ++i_;
    return *this;
  }
  array_const_iterator operator++(int) {
    array_const_iterator copy = *this;
    ++*this;
    return copy;
  }
  array_const_iterator &operator--() {
    --i_;
    return *this;
  }
  array_const_iterator operator--(int) {
    array_const_iterator copy = *this;
    --*this;
    return copy;
  }
  // comparsion
  // 写経したけどa_も同じオブジェクトか調べたほうがいい?
  bool operator==(array_const_iterator const &right) { return i_ == right.i_; }
  bool operator!=(array_const_iterator const &right) { return i_ != right.i_; }
  bool operator>(array_const_iterator const &right) { return i_ > right.i_; }
  bool operator>=(array_const_iterator const &right) {
    return *this == right || *this > right;
  }
  bool operator<(array_const_iterator const &right) { return i_ < right.i_; }
  bool operator<=(array_const_iterator const &right) {
    return *this == right || *this < right;
  }
  // alithmetic
  array_const_iterator &operator+=(std::size_t n) {
    i_ += n;
    return *this;
  }
  array_const_iterator operator+(std::size_t n) const {
    auto copy = *this;
    copy += n;
    return copy;
  }
  array_const_iterator &operator-=(std::size_t n) {
    i_ -= n;
    return *this;
  }
  array_const_iterator operator-(std::size_t n) const {
    auto copy = *this;
    copy -= n;
    return copy;
  }
  // subscript
  typename Array::const_reference operator[](std::size_t n) const {
    return *(*this + n);
  }
  typename Array::const_reference operator*() const { return a_[i_]; };
};

#endif /* ARRAY_HPP */
