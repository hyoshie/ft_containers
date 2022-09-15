#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft {

// ----------------------------------------------------
// tag
// ----------------------------------------------------

// struct input_iterator_tag {};
// struct output_iterator_tag {};
// struct forward_iterator_tag : public input_iterator_tag {};
// struct bidirectional_iterator_tag : public forward_iterator_tag {};
// struct random_access_iterator_tag : public bidirectional_iterator_tag {};
// struct contiguous_iterator_tag : public random_access_iterator_tag {};

// ----------------------------------------------------
// iterator_traits
// ----------------------------------------------------

template < typename Iterator >
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

// specialization for pointer types
template < typename Tp >
struct iterator_traits< Tp* > {
  typedef std::random_access_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef ptrdiff_t difference_type;
  typedef Tp* pointer;
  typedef Tp& reference;
};

// specialization for const pointer types
template < typename Tp >
struct iterator_traits< const Tp* > {
  typedef std::random_access_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef ptrdiff_t difference_type;
  typedef const Tp* pointer;
  typedef const Tp& reference;
};

// ----------------------------------------------------
// iterator
// ----------------------------------------------------
template < typename Category, typename T, typename Distance = std::ptrdiff_t,
           typename Pointer = T*, typename Reference = T& >
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

// ----------------------------------------------------
// reverse_iterator
// ----------------------------------------------------
template < class Iter >
class reverse_iterator
    : public ft::iterator<
          typename ft::iterator_traits< Iter >::iterator_category,
          typename ft::iterator_traits< Iter >::value_type,
          typename ft::iterator_traits< Iter >::difference_type,
          typename ft::iterator_traits< Iter >::pointer,
          typename ft::iterator_traits< Iter >::reference > {
  // types
 protected:
  typedef ft::iterator_traits< Iter > traits_type;

 public:
  typedef Iter iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::difference_type difference_type;
  typedef typename traits_type::pointer pointer;
  typedef typename traits_type::reference reference;

  // method
  reverse_iterator() : current_(){};

  explicit reverse_iterator(iterator_type x) : current_(x){};

  template < class U >
  reverse_iterator(const reverse_iterator< U >& other)
      : current_(other.base()) {}

  template < class U >
  reverse_iterator& operator=(const reverse_iterator< U >& other) {
    if (this == &other) return *this;
    current_ = other.base();
    return *this;
  }

  virtual ~reverse_iterator() {}

  iterator_type base() const { return current_; }

  reference operator*() const {
    Iter tmp = current_;
    return *--tmp;
  }

  pointer operator->() const { return &(**this); };

  reference operator[](difference_type n) const { return *(*this + n); }

  reverse_iterator& operator++() {
    --current_;
    return *this;
  }

  reverse_iterator& operator--() {
    ++current_;
    return *this;
  }

  reverse_iterator operator++(int) {
    reverse_iterator tmp = *this;
    --current_;
    return tmp;
  }

  reverse_iterator operator--(int) {
    reverse_iterator tmp = *this;
    ++current_;
    return tmp;
  }

  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current_ - n);
  }

  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current_ + n);
  }

  reverse_iterator& operator+=(difference_type n) {
    current_ -= n;
    return *this;
  }

  reverse_iterator& operator-=(difference_type n) {
    current_ += n;
    return *this;
  }

 protected:
  Iter current_;
};

// non-member functions
template < class Iterator1, class Iterator2 >
bool operator==(const ft::reverse_iterator< Iterator1 >& lhs,
                const ft::reverse_iterator< Iterator2 >& rhs) {
  return lhs.base() == rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator!=(const ft::reverse_iterator< Iterator1 >& lhs,
                const ft::reverse_iterator< Iterator2 >& rhs) {
  return !(lhs == rhs);
}

template < class Iterator1, class Iterator2 >
bool operator<(const ft::reverse_iterator< Iterator1 >& lhs,
               const ft::reverse_iterator< Iterator2 >& rhs) {
  return lhs.base() > rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator<=(const ft::reverse_iterator< Iterator1 >& lhs,
                const ft::reverse_iterator< Iterator2 >& rhs) {
  return !(lhs > rhs);
}

template < class Iterator1, class Iterator2 >
bool operator>(const ft::reverse_iterator< Iterator1 >& lhs,
               const ft::reverse_iterator< Iterator2 >& rhs) {
  return lhs.base() < rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator>=(const ft::reverse_iterator< Iterator1 >& lhs,
                const ft::reverse_iterator< Iterator2 >& rhs) {
  return !(lhs < rhs);
}

template < class Iter >
reverse_iterator< Iter > operator+(
    typename reverse_iterator< Iter >::difference_type n,
    const reverse_iterator< Iter >& it) {
  reverse_iterator< Iter >(it.base() - n);
}

template < class Iterator >
typename reverse_iterator< Iterator >::difference_type operator-(
    const reverse_iterator< Iterator >& lhs,
    const reverse_iterator< Iterator >& rhs) {
  return rhs.base() - lhs.base();
}

// ----------------------------------------------------
// random_access_iterator
// ----------------------------------------------------

template < class T >
class random_access_iterator
    : public ft::iterator< std::random_access_iterator_tag, T > {
  // types
 public:
  typedef typename ft::iterator< std::random_access_iterator_tag,
                                 T >::iterator_category iterator_category;
  typedef
      typename ft::iterator< std::random_access_iterator_tag, T >::value_type
          value_type;
  typedef typename ft::iterator< std::random_access_iterator_tag,
                                 T >::difference_type difference_type;
  typedef T* pointer;
  typedef T& reference;

  // method
  random_access_iterator() : current_(NULL) {}

  explicit random_access_iterator(pointer x) : current_(x) {}

  template < class U >
  random_access_iterator(const random_access_iterator< U >& other) {
    current_ = other.base();
  }

  template < class U >
  random_access_iterator& operator=(const random_access_iterator< U >& other) {
    if (this == &other) return *this;
    current_ = other.base();
    return *this;
  }

  virtual ~random_access_iterator() {}

  pointer base() const { return current_; }

  reference operator*() const { return *current_; }

  pointer operator->() const { return current_; }

  reference operator[](difference_type n) const { return *(*this + n); }

  random_access_iterator& operator++() {
    ++current_;
    return *this;
  }

  random_access_iterator& operator--() {
    --current_;
    return *this;
  }

  random_access_iterator operator++(int) {
    random_access_iterator tmp = *this;
    ++current_;
    return tmp;
  }

  random_access_iterator operator--(int) {
    random_access_iterator tmp = *this;
    --current_;
    return tmp;
  }

  random_access_iterator operator+(difference_type n) const {
    return random_access_iterator(current_ + n);
  }

  random_access_iterator operator-(difference_type n) const {
    return random_access_iterator(current_ - n);
  }

  random_access_iterator& operator+=(difference_type n) {
    current_ += n;
    return *this;
  }

  random_access_iterator& operator-=(difference_type n) {
    current_ -= n;
    return *this;
  }

  // operator random_access_iterator< const T >() {
  //   return random_access_iterator< const T >(current_);
  // }

 protected:
  pointer current_;
};

// non-member functions
template < class Iterator1, class Iterator2 >
bool operator==(const ft::random_access_iterator< Iterator1 >& lhs,
                const ft::random_access_iterator< Iterator2 >& rhs) {
  return lhs.base() == rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator!=(const ft::random_access_iterator< Iterator1 >& lhs,
                const ft::random_access_iterator< Iterator2 >& rhs) {
  return !(lhs == rhs);
}

template < class Iterator1, class Iterator2 >
bool operator<(const ft::random_access_iterator< Iterator1 >& lhs,
               const ft::random_access_iterator< Iterator2 >& rhs) {
  return lhs.base() < rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator<=(const ft::random_access_iterator< Iterator1 >& lhs,
                const ft::random_access_iterator< Iterator2 >& rhs) {
  return !(lhs > rhs);
}

template < class Iterator1, class Iterator2 >
bool operator>(const ft::random_access_iterator< Iterator1 >& lhs,
               const ft::random_access_iterator< Iterator2 >& rhs) {
  return lhs.base() > rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator>=(const ft::random_access_iterator< Iterator1 >& lhs,
                const ft::random_access_iterator< Iterator2 >& rhs) {
  return !(lhs < rhs);
}

template < class Iter >
random_access_iterator< Iter > operator+(
    typename random_access_iterator< Iter >::difference_type n,
    const random_access_iterator< Iter >& it) {
  random_access_iterator< Iter >(it.base() + n);
}

template < class Iterator >
typename random_access_iterator< Iterator >::difference_type operator-(
    const random_access_iterator< Iterator >& lhs,
    const random_access_iterator< Iterator >& rhs) {
  return lhs.base() - rhs.base();
}
}  // namespace ft

// ----------------------------------------------------
// memo
// ----------------------------------------------------
// iterator のconst とnon-constの比較
// const対応

#endif /* ITERATOR_HPP */
