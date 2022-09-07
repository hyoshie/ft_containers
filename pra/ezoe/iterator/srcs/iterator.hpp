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
// reverse_iterator
// ----------------------------------------------------

}  // namespace ft

#endif /* ITERATOR_HPP */
