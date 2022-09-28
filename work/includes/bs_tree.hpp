#ifndef BS_TREE_HPP
#define BS_TREE_HPP

#include <cassert>

#include "iterator.hpp"
#include "pair.hpp"
#include "util.hpp"

namespace ft {

template < typename T >
struct bs_tree_node {
  typedef bs_tree_node< T >* node_ptr;
  node_ptr parent;
  node_ptr left;
  node_ptr right;
  T item;
  bs_tree_node() : parent(NULL), left(NULL), right(NULL) {}
  bs_tree_node(const T& given)
      : parent(NULL), left(NULL), right(NULL), item(given) {}
};

template < class Node >
static Node* next(Node* node, Node* nil) {
  // only dummy, size = 0
  if (node->right == node) {
    return node;
  }
  if (node->right != nil) {
    node = node->right;
    while (node != nil && node->left != nil) {
      node = node->left;
    }
  } else {
    Node* next = node->parent;
    while (next != nil && next->right == node) {
      node = next;
      next = next->parent;
    }
    // dummy->nextのsegv対策
    if (next) {
      node = next;
    }
  }
  return node;
}

template < class Node >
static Node* prev(Node* node, Node* nil) {
  // only dummy, size = 0
  if (node->right == node) {
    return node;
  }
  if (node->left != nil) {
    node = node->left;
    while (node != nil && node->right != nil) {
      node = node->right;
    }
  } else {
    Node* next = node->parent;
    while (next->left == node && next->parent != nil) {
      node = next;
      next = next->parent;
    }
    node = next;
  }
  return node;
}

template < class T >
struct bs_tree_const_iterator;

template < class T >
struct bs_tree_iterator
    : public ft::iterator< std::bidirectional_iterator_tag, T > {
  // types
 private:
  typedef typename ft::iterator< std::bidirectional_iterator_tag, T >
      base_iterator;
  typedef bs_tree_const_iterator< T > const_iterator;

 public:
  typedef typename base_iterator::iterator_category iterator_category;
  typedef typename base_iterator::value_type value_type;
  typedef typename base_iterator::difference_type difference_type;
  typedef T* pointer;
  typedef T& reference;
  typedef bs_tree_iterator< T > self;
  typedef typename bs_tree_node< T >::node_ptr node_ptr;

  // method
  bs_tree_iterator() : current_(node_ptr()), nil_(NULL) {}

  bs_tree_iterator(node_ptr x, node_ptr nil) : current_(x), nil_(nil) {}

  virtual ~bs_tree_iterator() {}

  reference operator*() const { return current_->item; }

  pointer operator->() const { return &current_->item; }

  self& operator++() {
    current_ = next(current_, nil_);
    return *this;
  }

  self& operator--() {
    current_ = prev(current_, nil_);
    return *this;
  }

  self operator++(int) {
    bs_tree_iterator tmp = *this;
    current_ = next(current_, nil_);
    return tmp;
  }

  self operator--(int) {
    bs_tree_iterator tmp = *this;
    current_ = prev(current_, nil_);
    return tmp;
  }

  bool operator==(const self& rhs) const { return current_ == rhs.current_; }
  bool operator==(const const_iterator& rhs) const {
    return current_ == rhs.current_;
  }

  bool operator!=(const self& rhs) const { return !(current_ == rhs.current_); }
  bool operator!=(const const_iterator& rhs) const {
    return !(current_ == rhs.current_);
  }

  node_ptr current_;
  node_ptr nil_;
};

template < class T >
struct bs_tree_const_iterator
    : public ft::iterator< std::bidirectional_iterator_tag, T > {
  // types
 private:
  typedef typename ft::iterator< std::bidirectional_iterator_tag, T >
      base_iterator;
  typedef bs_tree_iterator< T > iterator;

 public:
  typedef typename base_iterator::iterator_category iterator_category;
  typedef typename base_iterator::value_type value_type;
  typedef typename base_iterator::difference_type difference_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef bs_tree_const_iterator< T > self;
  typedef typename bs_tree_node< T >::node_ptr node_ptr;

  // method
  bs_tree_const_iterator() : current_(node_ptr()), nil_(NULL) {}

  bs_tree_const_iterator(node_ptr x, node_ptr nil) : current_(x), nil_(nil) {}

  bs_tree_const_iterator(const iterator& it)
      : current_(it.current_), nil_(it.nil_) {}

  virtual ~bs_tree_const_iterator() {}

  // いつ使う？標準ライブラリにあった
  // iterator m_const_cast() const {
  //   return iterator(const_cast< typename iterator::node_ptr >(current_));
  // }

  reference operator*() const { return current_->item; }

  pointer operator->() const { return &current_->item; }

  self& operator++() {
    current_ = next(current_, nil_);
    return *this;
  }

  self& operator--() {
    current_ = prev(current_, nil_);
    return *this;
  }

  self operator++(int) {
    bs_tree_const_iterator tmp = *this;
    current_ = next(current_, nil_);
    return tmp;
  }

  self operator--(int) {
    bs_tree_const_iterator tmp = *this;
    current_ = prev(current_, nil_);
    return tmp;
  }

  bool operator==(const self& rhs) const { return current_ == rhs.current_; }

  bool operator!=(const self& rhs) const { return current_ != rhs.current_; }

  node_ptr current_;
  node_ptr nil_;
};

template < class Key, class Value, class Compare,
           class Allocator = std::allocator< Value > >
class bs_tree {
  // 型
 private:
  typedef bs_tree_node< Value > node_type;
  typedef bs_tree_node< Value >* node_ptr;
  typedef const bs_tree_node< Value >* const_node_ptr;
  typedef typename Allocator::template rebind< bs_tree_node< Value > >::other
      node_allocator;

 public:
  typedef Key key_type;
  typedef Value value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef Allocator allocator_type;
  typedef Compare key_compare;

  typedef bs_tree_iterator< value_type > iterator;
  typedef bs_tree_const_iterator< value_type > const_iterator;
  typedef ft::reverse_iterator< iterator > reverse_iterator;
  typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;

  // メンバ関数
  bs_tree()
      : nil_(NULL),
        comp_func_(key_compare()),
        node_alloc_(node_allocator()),
        count_(0) {
    header_ = create_node(value_type());
    header_->parent = nil_;
    header_->left = nil_;
    header_->right = nil_;
    most_left_ = header_;
    most_right_ = header_;
  }

  explicit bs_tree(const Compare& comp, const Allocator& alloc)
      : nil_(NULL),
        comp_func_(comp),
        node_alloc_(node_allocator(alloc)),
        count_(0) {
    header_ = create_node(value_type());
    header_->parent = nil_;
    header_->left = nil_;
    header_->right = nil_;
    most_left_ = header_;
    most_right_ = header_;
  }

  // bs_tree(const bs_tree&)
  virtual ~bs_tree() {
    destroy_tree(root());
    destroy_node(nil_);
    destroy_node(header_);
  }

  // イテレータ
  iterator begin() { return iterator(most_left_, nil_); }
  const_iterator begin() const { return const_iterator(most_left_, nil_); }

  iterator end() { return iterator(header_, nil_); }
  const_iterator end() const { return const_iterator(header_, nil_); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // map側で対応, mapped_type作ってないので
  // // 要素アクセス
  // T& operator[](const Key& search_key) {
  //   iterator it = lower_bound(search_key);
  //   // 要素が見つからない場合
  //   if (it == end() || comp_func_(search_key, it->first))
  //     it = insert(it, value_type(search_key, mapped_type()));
  //   return it->second;
  // }

  // 容量
  bool empty() const { return (count_ == 0); }

  size_type size() const { return count_; }

  // テストしてない
  size_type max_size() const { return node_alloc_.max_size(); }

  // 容量
  void clear() {
    destroy_tree(root());
    connect_root_to_header(nil_);
    count_ = 0;
  }

  ft::pair< iterator, bool > insert(const value_type& value) {
    node_ptr ptr = find_last(key(value));
    if (ptr != nil_ && key(ptr) == key(value)) {
      return ft::make_pair(iterator(ptr, nil_), false);
    }
    node_ptr new_node = create_node(value);
    bool has_added = add_child(ptr, new_node);
    // 失敗しない
    assert(has_added);
    return ft::make_pair(iterator(new_node, nil_), true);
  }

  // 時間があれば対応
  iterator insert(iterator hint, const value_type& value) {
    (void)hint;
    return insert(value).first;
  }

  template < class InputIt >
  void insert(InputIt first, InputIt last) {
    for (; first != last; first++) {
      insert(*first);
    }
  }

  void erase(iterator pos) { erase(pos->first); }

  void erase(iterator first, iterator last) {
    while (first != last) {
      erase(first++);
    }
  }

  size_type erase(const key_type& key) { return remove(key); }

  // 検索
  size_type count(const Key& key) const { return (find_equal(key) != nil_); }

  iterator find(const Key& key) {
    node_ptr node = find_equal(key);
    return (node != nil_) ? iterator(node, nil_) : end();
  }

  const_iterator find(const Key& key) const {
    node_ptr node = find_equal(key);
    return (node != nil_) ? const_iterator(node, nil_) : end();
  }

  iterator lower_bound(const Key& key) {
    return iterator(find_lower_bound(key), nil_);
  }

  const_iterator lower_bound(const Key& key) const {
    return const_iterator(find_lower_bound(key), nil_);
  }

  iterator upper_bound(const Key& key) {
    return iterator(find_upper_bound(key), nil_);
  }

  const_iterator upper_bound(const Key& key) const {
    return const_iterator(find_upper_bound(key), nil_);
  }

  ft::pair< iterator, iterator > equal_range(const Key& key) {
    iterator lower = lower_bound(key);
    iterator upper = upper_bound(key);
    return ft::make_pair(lower, upper);
  }
  ft::pair< const_iterator, const_iterator > equal_range(const Key& key) const {
    const_iterator lower = lower_bound(key);
    const_iterator upper = upper_bound(key);
    return ft::make_pair(lower, upper);
  }

  //テスト用
  node_ptr header() { return header_; }
  node_ptr nil() { return nil_; }
  node_ptr root() { return header_->left; }
  node_ptr root() const { return header_->left; }

  // debug
  void print() {
    value_type left_item = most_left_->item;
    value_type right_item = most_right_->item;
    std::cout << "most_left :(" << left_item.first << ", " << left_item.second
              << ")" << std::endl;
    std::cout << "most_right:(" << right_item.first << ", " << right_item.second
              << ")" << std::endl;
    print_graph(root(), 0);
  }

  void print_with_itr() const {
    std::cerr << "[\x1b[32mPRINT_WITH_ITR\x1b[39m]" << std::endl;
    for (const_iterator it = begin(); it != end(); it++) {
      std::cerr << "(" << it.current_ << "):" << it->first << ", " << it->second
                << std::endl;
      std::cerr << "(" << it.current_->parent << "):parent" << std::endl;
      std::cerr << "(" << it.current_->left << "):left" << std::endl;
      std::cerr << "(" << it.current_->right << "):right" << std::endl;
      std::cerr << std::endl;
    }
    std::cerr << "[\x1b[32mEND_ITR\x1b[39m]" << std::endl;
  }

 private:
  // メンバ関数
  // 木やノードの特定の値を取り出す
  key_type key(node_ptr node) { return node->item.first; }
  key_type key(const_node_ptr node) const { return node->item.first; }
  key_type key(const_reference value) { return value.first; }
  key_type key(const_reference value) const { return value.first; }

  node_ptr most_left(node_ptr node) {
    if (node == nil_) {
      return header_;
    }
    while (node != nil_ && node->left != nil_) {
      node = node->left;
    }
    return node;
  }

  node_ptr most_right(node_ptr node) {
    if (node == nil_) {
      return header_;
    }
    while (node != nil_ && node->right != nil_) {
      node = node->right;
    }
    return node;
  }

  // ヘッダーやルートの更新
  void connect_root_to_header(node_ptr new_root) {
    header_->left = new_root;
    if (new_root != nil_) {
      new_root->parent = header_;
    }
  }

  void update_header() {
    most_left_ = most_left(root());
    most_right_ = most_right(root());
  }

  // メモリ関連
  node_ptr allocate(size_type n) { return node_alloc_.allocate(n); }

  void deallocate(node_ptr ptr, size_type n) { node_alloc_.deallocate(ptr, n); }

  void construct(node_ptr ptr) { node_alloc_.construct(ptr, node_type()); }

  void construct(node_ptr ptr, const_reference value) {
    node_alloc_.construct(ptr, value);
  }

  void destroy(node_ptr ptr) { node_alloc_.destroy(ptr); }

  node_ptr create_node(const_reference value) {
    node_ptr new_node = allocate(1);
    construct(new_node, value);
    return new_node;
  }

  void destroy_node(node_ptr ptr) {
    destroy(ptr);
    deallocate(ptr, 1);
  }

  void destroy_tree(node_ptr root) {
    if (root != nil_) {
      destroy_tree(root->left);
      destroy_tree(root->right);
      destroy_node(root);
    }
  }

  // add, remove, findのヘルパー
  node_ptr find_last(const key_type& search_key) {
    node_ptr current = root();
    node_ptr prev = nil_;
    while (current != nil_) {
      prev = current;
      if (search_key == key(current)) {
        return current;  // x.item はすでに木に含まれている
      }
      bool comp = comp_func_(search_key, key(current));
      if (comp) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return prev;
  }

  // 本当はprivate、テストのためpublicに
 public:
  node_ptr find_equal(const key_type& search_key) const {
    node_ptr current = root();
    node_ptr prev = nil_;
    while (current != nil_) {
      prev = current;
      if (search_key == key(current)) {
        return current;  // x.item はすでに木に含まれている
      }
      bool comp = comp_func_(search_key, key(current));
      if (comp) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return nil_;
  }

 private:
  node_ptr find_lower_bound(const key_type& search_key) const {
    node_ptr current = root();
    node_ptr prev = header_;  //見つからない場合end()を返すため
    while (current != nil_) {
      if (search_key == key(current)) {
        return current;
      }
      bool comp = comp_func_(search_key, key(current));
      if (comp) {
        prev = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return prev;
  }

  node_ptr find_upper_bound(const key_type& search_key) const {
    node_ptr current = root();
    node_ptr prev = header_;  //見つからない場合end()を返すため
    while (current != nil_) {
      if (search_key == key(current)) {
        current = current->left;
      } else {
        bool comp = comp_func_(search_key, key(current));
        if (comp) {
          prev = current;
          current = current->left;
        } else {
          current = current->right;
        }
      }
    }
    return prev;
  }

  bool add_child(node_ptr ptr, node_ptr to_insert) {
    if (ptr == nil_) {
      connect_root_to_header(to_insert);
    } else {
      if (key(to_insert) == key(ptr)) {
        return false;  // to_insert.item はすでに木に含まれている
      }
      bool comp = comp_func_(key(to_insert), key(ptr));
      if (comp) {
        ptr->left = to_insert;
      } else {
        ptr->right = to_insert;
      }
      to_insert->parent = ptr;
    }
    count_++;
    update_header();
    return true;
  }

  void connect_parent_to_new_child(node_ptr new_child, node_ptr old_child) {
    node_ptr parent = old_child->parent;
    if (parent == nil_) {
      return;
    }
    if (parent->left == old_child) {
      parent->left = new_child;
    } else {
      parent->right = new_child;
    }
  }

  // 隣り合うノードの位置を入れ替える
  // swap_node_positionと1つにできるが、後回し
  void swap_node_right_link(node_ptr parent, node_ptr right_child) {
    connect_parent_to_new_child(right_child, parent);
    node_type tmp;
    tmp.parent = parent->parent;
    tmp.left = parent->left;
    tmp.right = parent->right;

    parent->parent = right_child;
    parent->left = right_child->left;
    parent->right = right_child->right;

    right_child->parent = tmp.parent;
    right_child->left = tmp.left;
    right_child->right = parent;
  }

  // 2つのノードの位置を入れ替える
  void swap_node_position(node_ptr node1, node_ptr node2) {
    connect_parent_to_new_child(node1, node2);
    connect_parent_to_new_child(node2, node1);
    std::swap(node1->parent, node2->parent);
    std::swap(node1->left, node2->left);
    std::swap(node1->right, node2->right);
  }

  bool remove(const key_type& search_key) {
    node_ptr ptr = find_last(search_key);
    if (ptr != nil_ && search_key == key(ptr)) {
      remove(ptr);
      return true;
    }
    return false;
  }

  void remove(node_ptr ptr) {
    if (ptr->left == nil_ || ptr->right == nil_) {
      splice(ptr);
      // destroy(ptr);
      destroy_node(ptr);
    } else {
      node_ptr target = most_left(ptr->right);
      if (target == ptr->right) {
        swap_node_right_link(ptr, target);
      } else {
        swap_node_position(ptr, target);
      }
      if (ptr == root()) {
        header_->left = target;
      }
      splice(ptr);
      // destroy(ptr);
      destroy_node(ptr);
    }
    count_--;
    update_header();
  }

  void splice(node_ptr ptr) {
    node_ptr child = (ptr->left != nil_) ? ptr->left : ptr->right;
    node_ptr new_parent = nil_;

    if (ptr == root()) {
      new_parent = header_;
      connect_root_to_header(child);
    } else {
      new_parent = ptr->parent;
      connect_parent_to_new_child(child, ptr);
    }
    if (child != nil_) {
      child->parent = new_parent;
    }
  }

  // debug
  void print_graph(node_ptr node, int depth) {
    if (node == nil_) {
      return;
    }
    print_graph(node->left, depth + 1);

    for (int i = 0; i < depth * 2; i++) {
      std::cout << " ";
    }
    std::cout << "+(" << node->item.first << ", " << node->item.second << ")"
              << std::endl;

    print_graph(node->right, depth + 1);
  }

  void print_itr(iterator iter) {
    std::cerr << "[\x1b[32mITERATOR\x1b[39m]" << std::endl;
    std::cerr << "(" << iter.current_ << "):" << iter->first << ", "
              << iter->second << std::endl;
    std::cerr << "(" << iter.current_->parent << "):parent" << std::endl;
    std::cerr << "(" << iter.current_->left << "):left" << std::endl;
    std::cerr << "(" << iter.current_->right << "):right" << std::endl;
    std::cerr << std::endl;
    std::cerr << "[\x1b[32mEND_PRINT\x1b[39m]" << std::endl;
  }

  void print_node(node_ptr node) {
    std::cerr << "[\x1b[32mPOINTER\x1b[39m]" << std::endl;
    std::cerr << "(" << node << "):" << node->item.first << ", "
              << node->item.second << std::endl;
    std::cerr << "(" << node->parent << "):parent" << std::endl;
    std::cerr << "(" << node->left << "):left" << std::endl;
    std::cerr << "(" << node->right << "):right" << std::endl;
    std::cerr << std::endl;
    std::cerr << "[\x1b[32mEND_PRINT\x1b[39m]" << std::endl;
  }

  // メンバ変数
  node_ptr header_;
  node_ptr most_left_;
  node_ptr most_right_;
  node_ptr nil_;
  key_compare comp_func_;
  node_allocator node_alloc_;
  size_type count_;
};

template < class Key, class Value, class Compare, class Alloc >
bool operator==(const ft::bs_tree< Key, Value, Compare, Alloc >& lhs,
                const ft::bs_tree< Key, Value, Compare, Alloc >& rhs) {
  return (lhs.size() == rhs.size()) &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template < class Key, class Value, class Compare, class Alloc >
bool operator!=(const ft::bs_tree< Key, Value, Compare, Alloc >& lhs,
                const ft::bs_tree< Key, Value, Compare, Alloc >& rhs) {
  return !(lhs == rhs);
}

template < class Key, class Value, class Compare, class Alloc >
bool operator<(const ft::bs_tree< Key, Value, Compare, Alloc >& lhs,
               const ft::bs_tree< Key, Value, Compare, Alloc >& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template < class Key, class Value, class Compare, class Alloc >
bool operator<=(const ft::bs_tree< Key, Value, Compare, Alloc >& lhs,
                const ft::bs_tree< Key, Value, Compare, Alloc >& rhs) {
  return !(rhs < lhs);
}

template < class Key, class Value, class Compare, class Alloc >
bool operator>(const ft::bs_tree< Key, Value, Compare, Alloc >& lhs,
               const ft::bs_tree< Key, Value, Compare, Alloc >& rhs) {
  return rhs < lhs;
}

template < class Key, class Value, class Compare, class Alloc >
bool operator>=(const ft::bs_tree< Key, Value, Compare, Alloc >& lhs,
                const ft::bs_tree< Key, Value, Compare, Alloc >& rhs) {
  return !(lhs < rhs);
}
}  // namespace ft

#endif /* BS_TREE_HPP */
