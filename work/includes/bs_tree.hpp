#ifndef BS_TREE_HPP
#define BS_TREE_HPP

template < typename T >
struct bs_tree_node {
  typedef bs_tree_node< T >* link_type;
  link_type parent;
  link_type left;
  link_type right;
  T item;
  bs_tree_node() : parent(NULL), left(NULL), right(NULL) {}
  bs_tree_node(const T& given)
      : parent(NULL), left(NULL), right(NULL), item(given) {}
};

template < class Key, class Value, class Compare,
           class Allocator = std::allocator< Value > >
class bs_tree {
  // 型
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
    // root_ = allocate(1);
    // construct(root_);
    root_ = NULL;
  }

  bool add(const_reference x) {
    link_type ptr = findLast(x);
    link_type u = new bs_tree_node< Value >;
    u->item = x;
    // std::cout << u->item.first << std::endl;
    return addChild(ptr, u);
  }
  // debug
  void print() {
    ;
    // std::cout << root_->item.first << std::endl;
    // std::cout << root_->item.second << std::endl;
    print_graph(root_, 0);
  }

 private:
  // 型
  typedef bs_tree_node< Value >* link_type;
  typedef const bs_tree_node< Value >* const_link_type;
  typedef typename Allocator::template rebind< bs_tree_node< Value > >::other
      node_allocator;

  // メンバ関数
  link_type allocate(size_type n) { return node_alloc_.allocate(n); }

  void construct(link_type ptr) {
    node_alloc_.construct(ptr, bs_tree_node< Value >());
  }

  void construct(link_type ptr, const Value& value) {
    node_alloc_.construct(ptr, value);
  }

  link_type findLast(const_reference x) {
    link_type current = root_;
    link_type prev = nil_;
    while (current != nil_) {
      prev = current;
      if (x.first == current->item.first) {
        return current;  // x.item はすでに木に含まれている
      }
      bool comp = comp_func_(x.first, current->item.first);
      if (comp) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return prev;
  }

  bool addChild(link_type ptr, link_type to_insert) {
    if (ptr == nil_) {
      root_ = to_insert;  // 空っぽの木に挿入する
    } else {
      if (to_insert->item.first == ptr->item.first) {
        return false;  // to_insert.item はすでに木に含まれている
      }
      bool comp = comp_func_(to_insert->item.first, ptr->item.first);
      if (comp) {
        ptr->left = to_insert;
      } else {
        ptr->right = to_insert;
      }
      to_insert->parent = ptr;
    }
    // n++;
    return true;
  }

  void print_graph(link_type node, int depth) {
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
  link_type root_;
  link_type nil_;
  key_compare comp_func_;
  node_allocator node_alloc_;
};

#endif /* BS_TREE_HPP */
