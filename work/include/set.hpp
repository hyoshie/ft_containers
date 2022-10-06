#ifndef SET_HPP
#define SET_HPP

#include <functional>

#include "rb_tree.hpp"
#include "util.hpp"

namespace ft {
template < class Key, class Compare = std::less< Key >,
           class Allocator = std::allocator< Key > >
class set {
  // メンバ型
 public:
  typedef Key key_type;
  typedef Key value_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Allocator allocator_type;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef typename Allocator::reference reference;
  typedef typename Allocator::const_reference const_reference;

 private:
  typedef rb_tree< key_type, value_type, ft::identity< value_type >,
                   key_compare, allocator_type >
      rep_type;

 public:
  typedef typename rep_type::iterator iterator;
  typedef typename rep_type::const_iterator const_iterator;
  typedef typename rep_type::size_type size_type;
  typedef typename rep_type::difference_type difference_type;
  typedef typename rep_type::reverse_iterator reverse_iterator;
  typedef typename rep_type::const_reverse_iterator const_reverse_iterator;

  // メンバ関数

  explicit set(const Compare& comp = Compare(),
               const Allocator& alloc = Allocator())
      : tree_(comp, alloc), key_comp_(comp) {}

  template < class InputIt >
  set(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator(),
      typename ft::enable_if< !ft::is_integral< InputIt >::value,
                              InputIt >::type* = NULL)
      : tree_(comp, alloc), key_comp_(comp) {
    insert(first, last);
  }

  set(const set& other) : tree_(other.tree_), key_comp_(other.key_comp_) {}

  ~set() {}

  set& operator=(const set& other) {
    if (this != &other) {
      tree_ = other.tree_;
    }
    return *this;
  }

  allocator_type get_allocator() const { return tree_.get_allocator(); }

  // イテレータ
  iterator begin() { return tree_.begin(); }
  const_iterator begin() const { return tree_.begin(); }

  iterator end() { return tree_.end(); }
  const_iterator end() const { return tree_.end(); }

  reverse_iterator rbegin() { return tree_.rbegin(); }
  const_reverse_iterator rbegin() const { return tree_.rbegin(); }

  reverse_iterator rend() { return tree_.rend(); }
  const_reverse_iterator rend() const { return tree_.rend(); }

  // 容量
  bool empty() const { return tree_.empty(); }

  size_type size() const { return tree_.size(); }

  size_type max_size() const { return tree_.max_size(); }

  // 変更
  void clear() { tree_.clear(); }

  ft::pair< iterator, bool > insert(const value_type& value) {
    return tree_.insert(value);
  }

  iterator insert(iterator hint, const value_type& value) {
    return tree_.insert(hint, value);
  }

  template < class InputIt >
  void insert(InputIt first, InputIt last) {
    tree_.insert(first, last);
  }

  void erase(iterator pos) { tree_.erase(pos); }

  void erase(iterator first, iterator last) { tree_.erase(first, last); }

  size_type erase(const key_type& key) { return tree_.erase(key); }

  void swap(set& other) { tree_.swap(other.tree_); }

  // 検索
  size_type count(const Key& key) const { return tree_.count(key); }

  iterator find(const Key& key) { return tree_.find(key); }

  const_iterator find(const Key& key) const { return tree_.find(key); }

  ft::pair< iterator, iterator > equal_range(const Key& key) {
    return tree_.equal_range(key);
  }

  ft::pair< const_iterator, const_iterator > equal_range(const Key& key) const {
    return tree_.equal_range(key);
  }

  iterator lower_bound(const Key& key) { return tree_.lower_bound(key); }

  const_iterator lower_bound(const Key& key) const {
    return tree_.lower_bound(key);
  }

  iterator upper_bound(const Key& key) { return tree_.upper_bound(key); }

  const_iterator upper_bound(const Key& key) const {
    return tree_.upper_bound(key);
  }

  // 観察
  key_compare key_comp() const { return key_comp_; }

  value_compare value_comp() const { return key_comp_; }

  // debug
  void print() const { tree_.print(); }

 private:
  rep_type tree_;
  key_compare key_comp_;
};

template < class Key, class Compare, class Alloc >
bool operator==(const ft::set< Key, Compare, Alloc >& lhs,
                const ft::set< Key, Compare, Alloc >& rhs) {
  return (lhs.size() == rhs.size()) &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template < class Key, class Compare, class Alloc >
bool operator!=(const ft::set< Key, Compare, Alloc >& lhs,
                const ft::set< Key, Compare, Alloc >& rhs) {
  return !(lhs == rhs);
}

template < class Key, class Compare, class Alloc >
bool operator<(const ft::set< Key, Compare, Alloc >& lhs,
               const ft::set< Key, Compare, Alloc >& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template < class Key, class Compare, class Alloc >
bool operator<=(const ft::set< Key, Compare, Alloc >& lhs,
                const ft::set< Key, Compare, Alloc >& rhs) {
  return !(rhs < lhs);
}

template < class Key, class Compare, class Alloc >
bool operator>(const ft::set< Key, Compare, Alloc >& lhs,
               const ft::set< Key, Compare, Alloc >& rhs) {
  return rhs < lhs;
}

template < class Key, class Compare, class Alloc >
bool operator>=(const ft::set< Key, Compare, Alloc >& lhs,
                const ft::set< Key, Compare, Alloc >& rhs) {
  return !(lhs < rhs);
}
}  // namespace ft

namespace std {
template < class Key, class Compare, class Alloc >
void swap(const ft::set< Key, Compare, Alloc >& lhs,
          const ft::set< Key, Compare, Alloc >& rhs) {
  lhs.swap(rhs);
}
}  // namespace std

#endif /* SET_HPP */
