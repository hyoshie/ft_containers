#ifndef MAP_HPP
#define MAP_HPP

#include <functional>

#include "rb_tree.hpp"

namespace ft {
template < class Key, class T, class Compare = std::less< Key >,
           class Allocator = std::allocator< ft::pair< const Key, T > > >
class map {
  // メンバ型
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair< const Key, T > value_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef typename Allocator::reference reference;
  typedef typename Allocator::const_reference const_reference;

 private:
  typedef rb_tree< key_type, value_type, ft::select1st< value_type >,
                   key_compare, allocator_type >
      rep_type;

 public:
  typedef typename rep_type::iterator iterator;
  typedef typename rep_type::const_iterator const_iterator;
  typedef typename rep_type::size_type size_type;
  typedef typename rep_type::difference_type difference_type;
  typedef typename rep_type::reverse_iterator reverse_iterator;
  typedef typename rep_type::const_reverse_iterator const_reverse_iterator;

  // メンバクラス
  class value_compare
      : public std::binary_function< value_type, value_type, bool > {
    friend class map< Key, T, Compare, Allocator >;

   protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

   public:
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

  // メンバ関数

  explicit map(const Compare& comp = Compare(),
               const Allocator& alloc = Allocator())
      : tree_(comp, alloc), key_comp_(comp), value_comp_(value_compare(comp)) {}

  template < class InputIt >
  map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator(),
      typename ft::enable_if< !ft::is_integral< InputIt >::value,
                              InputIt >::type* = NULL)
      : tree_(comp, alloc), key_comp_(comp), value_comp_(value_compare(comp)) {
    insert(first, last);
  }

  map(const map& other)
      : tree_(other.tree_),
        key_comp_(other.key_comp_),
        value_comp_(other.value_comp_) {}

  ~map() {}

  map& operator=(const map& other) {
    if (this != &other) {
      tree_ = other.tree_;
    }
    return *this;
  }

  allocator_type get_allocator() const { return tree_.get_allocator(); }

  // 要素アクセス
  T& operator[](const Key& key) {
    iterator it = find(key);
    if (it == end()) {
      it = insert(ft::make_pair(key, T())).first;
    }
    return it->second;
  }

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

  void swap(map& other) { tree_.swap(other.tree_); }

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

  value_compare value_comp() const { return value_comp_; }

  // debug
  void print() const { tree_.print(); }

 private:
  rep_type tree_;
  key_compare key_comp_;
  value_compare value_comp_;
};

template < class Key, class T, class Compare, class Alloc >
bool operator==(const ft::map< Key, T, Compare, Alloc >& lhs,
                const ft::map< Key, T, Compare, Alloc >& rhs) {
  return (lhs.size() == rhs.size()) &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template < class Key, class T, class Compare, class Alloc >
bool operator!=(const ft::map< Key, T, Compare, Alloc >& lhs,
                const ft::map< Key, T, Compare, Alloc >& rhs) {
  return !(lhs == rhs);
}

template < class Key, class T, class Compare, class Alloc >
bool operator<(const ft::map< Key, T, Compare, Alloc >& lhs,
               const ft::map< Key, T, Compare, Alloc >& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template < class Key, class T, class Compare, class Alloc >
bool operator<=(const ft::map< Key, T, Compare, Alloc >& lhs,
                const ft::map< Key, T, Compare, Alloc >& rhs) {
  return !(rhs < lhs);
}

template < class Key, class T, class Compare, class Alloc >
bool operator>(const ft::map< Key, T, Compare, Alloc >& lhs,
               const ft::map< Key, T, Compare, Alloc >& rhs) {
  return rhs < lhs;
}

template < class Key, class T, class Compare, class Alloc >
bool operator>=(const ft::map< Key, T, Compare, Alloc >& lhs,
                const ft::map< Key, T, Compare, Alloc >& rhs) {
  return !(lhs < rhs);
}

template < class Key, class T, class Compare, class Alloc >
void swap(const ft::map< Key, T, Compare, Alloc >& lhs,
          const ft::map< Key, T, Compare, Alloc >& rhs) {
  lhs.swap(rhs);
}

template < class Key, class T, class Compare, class Alloc >
void swap(ft::map< Key, T, Compare, Alloc >& lhs,
          ft::map< Key, T, Compare, Alloc >& rhs) {
  lhs.swap(rhs);
}

}  // namespace ft

namespace std {
template < class Key, class T, class Compare, class Alloc >
void swap(ft::map< Key, T, Compare, Alloc >& lhs,
          ft::map< Key, T, Compare, Alloc >& rhs) {
  lhs.swap(rhs);
}
}  // namespace std

#endif /* MAP_HPP */
