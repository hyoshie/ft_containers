#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft {

// ----------------------------------------------------
// tag
// ----------------------------------------------------

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
struct contiguous_iterator_tag : public random_access_iterator_tag {};

// ----------------------------------------------------
// iterator_traits
// ----------------------------------------------------

template <typename Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

// specialization for pointer types
template <typename Tp>
struct iterator_traits<Tp*> {
  typedef ft::random_access_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef ptrdiff_t difference_type;
  typedef Tp* pointer;
  typedef Tp& reference;
};

// specialization for const pointer types
template <typename Tp>
struct iterator_traits<const Tp*> {
  typedef ft::random_access_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef ptrdiff_t difference_type;
  typedef const Tp* pointer;
  typedef const Tp& reference;
};

// ----------------------------------------------------
// iterator
// ----------------------------------------------------
template <typename Category, typename T, typename Distance = std::ptrdiff_t,
          typename Pointer = T*, typename Reference = T&>
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
template <class Iter>
class reverse_iterator
    : public ft::iterator<typename ft::iterator_traits<Iter>::iterator_category,
                          typename ft::iterator_traits<Iter>::value_type,
                          typename ft::iterator_traits<Iter>::difference_type,
                          typename ft::iterator_traits<Iter>::pointer,
                          typename ft::iterator_traits<Iter>::reference> {
  // types
 public:
  typedef Iter iterator_type;
  typedef traits_type::iterator_category iterator_category;
  typedef traits_type::value_type value_type;
  typedef traits_type::difference_type difference_type;
  typedef traits_type::pointer pointer;
  typedef traits_type::reference reference;

  // method
  reverse_iterator() : current_(){};

  explicit reverse_iterator(iterator_type x) : current_(x){};

  template <class U>
  reverse_iterator(const reverse_iterator<U>& other)
      : current_(other.current_){};

  template <class U>
  reverse_iterator& operator=(const reverse_iterator<U>& other) {
    if (this == &other) return;
    current_ = other.current_;
    return *this;
  };

  iterator_type base() const { return current_; };

  reference operator*() const {
    Iter tmp = current_;
    return *--tmp;
  };

  pointer operator->() const { return &(**this); };

  reference operator[](difference_type n) const { return *(*this + n); };

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
  typedef ft::iterator_traits<Iter> traits_type;
}

// non-member functions
template <class Iterator1, class Iterator2>
bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return !(lhs == rhs);
}

template <class Iterator1, class Iterator2>
bool operator<(const ft::reverse_iterator<Iterator1>& lhs,
               const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() > rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return !(lhs < rhs);
}

template <class Iterator1, class Iterator2>
bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
               const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return !(lhs < rhs);
}

template <class Iter>
reverse_iterator<Iter> operator+(
    typename reverse_iterator<Iter>::difference_type n,
    const reverse_iterator<Iter>& it) {
  reverse_iterator<Iter>(it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
  return rhs.base() - lhs.base();
}

}  // namespace ft

#endif /* ITERATOR_HPP */
