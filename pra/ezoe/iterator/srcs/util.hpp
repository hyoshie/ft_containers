#ifndef UTIL_HPP
#define UTIL_HPP

template <typename Container>
void print(Container const& c) {
  for (std::size_t i = 0; i < c.size(); i++) {
    std::cout << c[i];
  }
  std::cout << std::endl;
}

template <typename InputIterator>
void print(InputIterator iter, InputIterator end_iter) {
  while (iter != end_iter) std::cout << *iter++;
  std::cerr << std::endl;
}

namespace ft {
// ----------------------------------------------------
// enagle_if
// ----------------------------------------------------
template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
  typedef T type;
};

// ----------------------------------------------------
// is_integral
// ----------------------------------------------------
template <typename T>
struct is_integral : public is_integral_helper<remove_cv<T>>::type {};

// is_integral_helper
template <typename>
struct is_integral_helper : public false_type {};

template <>
struct is_integral_helper<bool> : public true_type {};

template <>
struct is_integral_helper<char> : public true_type {};

template <>
struct is_integral_helper<signed char> : public true_type {};

template <>
struct is_integral_helper<unsigned char> : public true_type {};

template <>
struct is_integral_helper<wchar_t> : public true_type {};

template <>
struct is_integral_helper<short> : public true_type {};

template <>
struct is_integral_helper<unsigned short> : public true_type {};

template <>
struct is_integral_helper<int> : public true_type {};

template <>
struct is_integral_helper<unsigned int> : public true_type {};

template <>
struct is_integral_helper<long> : public true_type {};

template <>
struct is_integral_helper<unsigned long> : public true_type {};

template <>
struct is_integral_helper<long long> : public true_type {};

template <>
struct is_integral_helper<unsigned long long> : public true_type {};

// integral_constant
template <typename T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, v> type;
  const value_type operator()() const { return value; }
};

// The type used as a compile-time boolean with true value.
typedef true_type integral_constant<bool, true>;

/// The type used as a compile-time boolean with false value.
typedef false_type integral_constant<bool, false>;

// remove_cv
template <class T>
struct remove_cv {
  typedef T type;
};

template <class T>
struct remove_cv<const T> {
  typedef T type;
};

template <class T>
struct remove_cv<volatile T> {
  typedef T type;
};

template <class T>
struct remove_cv<const volatile T> {
  typedef T type;
};

};  // namespace ft

#endif /* UTIL_HPP */
