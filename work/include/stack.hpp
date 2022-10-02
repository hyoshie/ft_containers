#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
template < class T, class Container = ft::vector< T > >
class stack {
 public:
  // ネストされた型名
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

  // コンストラクタ
  explicit stack(const Container& cont = Container()) : c_(cont) {}
  stack(const stack& other) : c_(other.c_) {}

  // デストラクタ
  ~stack() {}

  stack& operator=(const stack& other) {
    if (this == &other) {
      return *this;
    }
    c_ = other.c_;
    return *this;
  }

  // 要素アクセス
  reference top() { return c_.back(); }
  const_reference top() const { return c_.back(); }

  // 容量
  bool empty() const { return c_.empty(); }

  size_type size() const { return c_.size(); }

  // 変更
  void push(const value_type& value) { c_.push_back(value); }

  void pop() { c_.pop_back(); }

  template < class T1, class Container1 >
  friend bool operator==(const ft::stack< T1, Container1 >& lhs,
                         const ft::stack< T1, Container1 >& rhs);

  template < class T1, class Container1 >
  friend bool operator<(const ft::stack< T1, Container1 >& lhs,
                        const ft::stack< T1, Container1 >& rhs);

 protected:
  Container c_;
};

template < class T, class Container >
bool operator==(const ft::stack< T, Container >& lhs,
                const ft::stack< T, Container >& rhs) {
  return lhs.c_ == rhs.c_;
}

template < class T, class Container >
bool operator!=(const ft::stack< T, Container >& lhs,
                const ft::stack< T, Container >& rhs) {
  return !(lhs == rhs);
}

template < class T, class Container >
bool operator<(const ft::stack< T, Container >& lhs,
               const ft::stack< T, Container >& rhs) {
  return lhs.c_ < rhs.c_;
}

template < class T, class Container >
bool operator<=(const ft::stack< T, Container >& lhs,
                const ft::stack< T, Container >& rhs) {
  return !(lhs > rhs);
}

template < class T, class Container >
bool operator>(const ft::stack< T, Container >& lhs,
               const ft::stack< T, Container >& rhs) {
  return rhs < lhs;
}

template < class T, class Container >
bool operator>=(const ft::stack< T, Container >& lhs,
                const ft::stack< T, Container >& rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

namespace std {}  // namespace std

#endif /* STACK_HPP */
