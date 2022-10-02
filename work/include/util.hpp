#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>

template < typename Container >
void print(Container const& c) {
  for (std::size_t i = 0; i < c.size(); i++) {
    std::cout << c[i];
  }
  std::cout << std::endl;
}

template < typename InputIterator >
void print(InputIterator iter, InputIterator end_iter) {
  while (iter != end_iter) std::cout << *iter++;
  std::cerr << std::endl;
}

namespace ft {
// ----------------------------------------------------
// enagle_if
// ----------------------------------------------------
template < bool B, class T = void >
struct enable_if {};

template < class T >
struct enable_if< true, T > {
  typedef T type;
};

// ----------------------------------------------------
// is_integral
// ----------------------------------------------------

// integral_constant
template < typename T, T v >
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant< T, v > type;
  const value_type operator()() const { return value; }
};

// The type used as a compile-time boolean with true value.
typedef integral_constant< bool, true > true_type;

/// The type used as a compile-time boolean with false value.

typedef integral_constant< bool, false > false_type;
// is_integral_helper
template < typename >
struct is_integral_helper : public false_type {};

template <>
struct is_integral_helper< bool > : public true_type {};

template <>
struct is_integral_helper< char > : public true_type {};

template <>
struct is_integral_helper< signed char > : public true_type {};

template <>
struct is_integral_helper< unsigned char > : public true_type {};

template <>
struct is_integral_helper< wchar_t > : public true_type {};

template <>
struct is_integral_helper< short > : public true_type {};

template <>
struct is_integral_helper< unsigned short > : public true_type {};

template <>
struct is_integral_helper< int > : public true_type {};

template <>
struct is_integral_helper< unsigned int > : public true_type {};

template <>
struct is_integral_helper< long > : public true_type {};

template <>
struct is_integral_helper< unsigned long > : public true_type {};

// vmでコンパイル時のエラーメッセージ
// わかもれで要確認
// ISO C++ 1998 does not support ‘long long’

// template <>
// struct is_integral_helper< long long > : public true_type {};

// template <>
// struct is_integral_helper< unsigned long long > : public true_type {};

// remove_cv
template < class T >
struct remove_cv {
  typedef T type;
};

template < class T >
struct remove_cv< const T > {
  typedef T type;
};

template < class T >
struct remove_cv< volatile T > {
  typedef T type;
};

template < class T >
struct remove_cv< const volatile T > {
  typedef T type;
};

template < typename T >
struct is_integral
    : public is_integral_helper< typename remove_cv< T >::type >::type {};

// ----------------------------------------------------
// equal
// ----------------------------------------------------

template < class InputIt1, class InputIt2 >
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!(*first1 == *first2)) {
      return false;
    }
  }
  return true;
}

template < class InputIt1, class InputIt2, class BinaryPredicate >
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
           BinaryPredicate p) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!p(*first1, *first2)) {
      return false;
    }
  }
  return true;
}

// ----------------------------------------------------
// lexicographical_compare
// ----------------------------------------------------

template < class InputIt1, class InputIt2 >
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
    if (*first1 < *first2) return true;
    if (*first2 < *first1) return false;
  }
  return (first1 == last1) && (first2 != last2);
}

template < class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2, Compare comp) {
  for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
    if (comp(*first1, *first2)) return true;
    if (comp(*first2, *first1)) return false;
  }
  return (first1 == last1) && (first2 != last2);
}

}  // namespace ft

#endif /* UTIL_HPP */
