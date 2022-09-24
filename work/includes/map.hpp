#ifndef MAP_HPP
#define MAP_HPP

#include "bs_tree.hpp"

namespace ft {
template < class Key, class T, class Compare = std::less< Key >,
           class Allocator = std::allocator< std::pair< const Key, T > > >
class map {
 private:
  typedef bs_tree< key_type, value_type, key_compare, allocator_type > Rep_type;
  Rep_type tree_;

  // メンバ型
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef std::pair< const Key, T > value_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef typename Allocator::reference reference;
  typedef typename Allocator::const_reference const_reference;
  typedef typename Rep_type::iterator iterator;
  typedef typename Rep_type::const_iterator const_iterator;
  typedef typename Rep_type::size_type size_type;
  typedef typename Rep_type::difference_type difference_type;
  typedef typename Rep_type::reverse_iterator reverse_iterator;
  typedef typename Rep_type::const_reverse_iterator const_reverse_iterator;

  // メンバクラス
  class value_compare
      : public std::binary_function< value_type, value_type, bool > {
    // protected:
    // friendが使えないため
   public:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

   public:
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

  // メンバ関数
  map() tree_() {}
  // 要素アクセス
  // イテレータ
  iterator begin() { return tree_.begin(); }
  const_iterator begin() const { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  const_iterator end() const { return tree_.end(); }
  reverse_iterator rbegin() { return tree_.rbegin(); }
  const_reverse_iterator rbegin() const { return tree_.rbegin(); }
  reverse_iterator rend() { return tree_.rend(); }
  const_reverse_iterator rend() const { return tree_.rend(); }
  bool empty() const { return tree_.empty(); }
  size_type size() const { return tree_.size(); }
  // 容量
  // 変更
  ft::pair< iterator, bool > insert(const value_type& value) {
    return tree_.insert(value);
  }
  // 検索
  iterator lower_bound(const Key& key) { return tree_.lower_bound(key); }
  const_iterator lower_bound(const Key& key) const {
    return tree_.lower_bound(key);
  }
  // 観察
}

}  // namespace ft

#endif /* MAP_HPP */
