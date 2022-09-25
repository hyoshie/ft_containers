#ifndef BS_TREE_HPP
#define BS_TREE_HPP

#include "iterator.hpp"

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

template < class T >
struct bs_tree_iterator
    : public ft::iterator< std::bidirectional_iterator_tag, T > {
  // types
 private:
  typedef typename ft::iterator< std::bidirectional_iterator_tag, T >
      base_iterator;

 public:
  typedef typename base_iterator::iterator_category iterator_category;
  typedef typename base_iterator::value_type value_type;
  typedef typename base_iterator::difference_type difference_type;
  typedef T* pointer;
  typedef T& reference;
  typedef bs_tree_iterator< T > self;
  typedef typename bs_tree_node< T >::node_ptr node_ptr;

  // method
  bs_tree_iterator() : current_() {}

  explicit bs_tree_iterator(node_ptr x) : current_(x) {}

  // template < class U >
  // bs_tree_iterator(const bs_tree_iterator< U >& other) {
  //   current_ = other.base();
  // }

  // template < class U >
  // bs_tree_iterator& operator=(const bs_tree_iterator< U >& other) {
  //   if (this == &other) return *this;
  //   current_ = other.base();
  //   return *this;
  // }

  virtual ~bs_tree_iterator() {}

  reference operator*() const { return current_->item; }

  pointer operator->() const { return &current_->item; }

  // bs_tree_iterator& operator++() {
  //   current_ = bs_tree_increment(current_);
  //   return *this;
  // }

  // bs_tree_iterator& operator--() {
  //   current_ = bs_tree_decrement(current_);
  //   return *this;
  // }

  // bs_tree_iterator operator++(int) {
  //   bs_tree_iterator tmp = *this;
  //   ++current_;
  //   return tmp;
  // }

  // bs_tree_iterator operator--(int) {
  //   bs_tree_iterator tmp = *this;
  //   --current_;
  //   return tmp;
  // }

  bool operator==(const self& rhs) const { return current_ == rhs.current_; }

  bool operator!=(const self& rhs) const { return current_ != rhs.current_; }

 protected:
  node_ptr current_;
};

// template < typename T >
// static bs_tree_node< T >* bs_tree_increment(bs_tree_node< T >* node) {
//   ;

//   return node;
// }

template < class Key, class Value, class Compare,
           class Allocator = std::allocator< Value > >
class bs_tree {
  // 型
 private:
  typedef bs_tree_node< Value > node;
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

  // メンバ関数
  bs_tree()
      : nil_(NULL), comp_func_(key_compare()), node_alloc_(node_allocator()) {
    header_ = create_node(value_type());
    header_->parent = nil_;
    header_->left = nil_;
    header_->right = nil_;
    most_left_ = nil_;
    most_right_ = nil_;
  }

  bool add(const_reference x) {
    node_ptr ptr = find_last(key(x));
    node_ptr u = create_node(x);
    return addChild(ptr, u);
  }

  bool remove(const_reference x) {
    node_ptr ptr = find_last(key(x));
    if (ptr != nil_ && key(x) == key(ptr)) {
      remove(ptr);
      return true;
    }
    return false;
  }

  //テスト用
  node_ptr header() { return header_; }
  node_ptr mostLeft() { return most_left_; }
  node_ptr mostRight() { return most_right_; }

  node_ptr next(node_ptr node) {
    // only dummy, size = 0
    if (node->right == node) {
      return node;
    }
    if (node->right != nil_) {
      node = most_left(node->right);
    } else {
      node_ptr next = node->parent;
      while (next != nil_ && next->right == node) {
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

  node_ptr prev(node_ptr node) {
    // only dummy, size = 0
    if (node->right == node) {
      return node;
    }
    if (node->left != nil_) {
      node = most_right(node->left);
    } else {
      node_ptr next = node->parent;
      while (next->left == node && next->parent != nil_) {
        node = next;
        next = next->parent;
      }
      node = next;
    }
    return node;
  }

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

 private:
  // メンバ関数
  // 木やノードの特定の値を取り出す
  key_type key(node_ptr node) { return node->item.first; }
  key_type key(const_node_ptr node) const { return node->item.first; }
  key_type key(const_reference value) { return value.first; }
  key_type key(const_reference value) const { return value.first; }

  //テスト用
 public:
  node_ptr root() { return header_->left; }
  node_ptr root() const { return header_->left; }

 private:
  void connect_root_to_header(node_ptr new_root) {
    header_->left = new_root;
    new_root->parent = header_;
  }

  void update_header() {
    most_left_ = most_left(root());
    most_right_ = most_right(root());
  }

  // node_ptr most_left() {
  //   node_ptr most_left = root();
  //   while (most_left != nil_ && most_left->left != nil_) {
  //     most_left = most_left->left;
  //   }
  //   return most_left;
  // }

  // node_ptr most_right() {
  //   node_ptr most_right = root();
  //   while (most_right != nil_ && most_right->right != nil_) {
  //     most_right = most_right->right;
  //   }
  //   return most_right;
  // }

  node_ptr most_left(node_ptr node) {
    // std::cout << header() << std::endl;
    // std::cout << node << std::endl;
    // std::cout << key(node) << std::endl;
    // std::cout << node->item.second << std::endl;
    while (node != nil_ && node->left != nil_) {
      // std::cerr << "[\x1b[32mmost\x1b[39m]" << std::endl;
      node = node->left;
    }
    return node;
  }

  node_ptr most_right(node_ptr node) {
    while (node != nil_ && node->right != nil_) {
      node = node->right;
    }
    return node;
  }

  // メモリ関連
  node_ptr allocate(size_type n) { return node_alloc_.allocate(n); }

  void construct(node_ptr ptr) { node_alloc_.construct(ptr, node()); }

  void construct(node_ptr ptr, const_reference value) {
    node_alloc_.construct(ptr, value);
  }

  node_ptr create_node(const_reference value) {
    node_ptr new_node = allocate(1);
    construct(new_node, value);
    return new_node;
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

 public:
  node_ptr find_equal(const key_type& search_key) {
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
    return NULL;
  }

 private:
  bool addChild(node_ptr ptr, node_ptr to_insert) {
    if (ptr == nil_) {
      // std::cerr << "[\x1b[32m1\x1b[39m]" << std::endl;
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
    // std::cerr << "[\x1b[32m2\x1b[39m]" << std::endl;
    // n++;
    update_header();
    return true;
  }

  void remove(node_ptr ptr) {
    if (ptr->left == nil_ || ptr->right == nil_) {
      splice(ptr);
      delete ptr;
    } else {
      node_ptr target = most_left(ptr->right);
      ptr->item = target->item;
      splice(target);
      delete target;
    }
    update_header();
  }

  void splice(node_ptr ptr) {
    node_ptr child;
    node_ptr new_parent;
    if (ptr->left != nil_) {
      child = ptr->left;
    } else {
      child = ptr->right;
    }
    if (ptr == root()) {
      connect_root_to_header(child);
      new_parent = nil_;
    } else {
      new_parent = ptr->parent;
      if (new_parent->left == ptr) {
        new_parent->left = child;
      } else {
        new_parent->right = child;
      }
    }
    if (child != nil_) {
      child->parent = new_parent;
    }
    // n--;
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
    std::cout << "+" << node->item.first << ", " << node->item.second
              << std::endl;

    print_graph(node->right, depth + 1);
  }

  // メンバ変数
  node_ptr header_;
  node_ptr most_left_;
  node_ptr most_right_;
  node_ptr nil_;
  key_compare comp_func_;
  node_allocator node_alloc_;
};

#endif /* BS_TREE_HPP */
