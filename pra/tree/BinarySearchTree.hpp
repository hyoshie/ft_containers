#ifndef TREE_HPP
#define TREE_HPP

#include <algorithm>

template < typename T >
struct Node {
  Node(T item = 0) : left(NULL), right(NULL), parent(NULL), item_(item) {}

  Node *left;
  Node *right;
  Node *parent;
  T item_;
};

template < typename T >
int depth(Node< T > *node) {
  int depth = 0;
  while (node) {
    node = node->parent;
    depth++;
  }
  return depth;
}

template < typename T >
int size(Node< T > *node) {
  if (!node) {
    return 0;
  }
  return 1 + size(node->left) + size(node->right);
}

template < typename T >
int height(Node< T > *node) {
  if (!node) {
    return -1;
  }
  return 1 + std::max(height(node->left), height(node->right));
}

template < typename T >
void print_node(Node< T > *node) {
  if (!node) {
    return;
  }
  // std::cout << "Node  : " << node << std::endl;
  std::cout << "item  : " << node->item_ << std::endl;
  if (node->left) {
    std::cout << "left  : " << node->left->item_ << std::endl;
  } else {
    std::cout << "left  : "
              << "NULL" << std::endl;
  }
  if (node->right) {
    std::cout << "right : " << node->right->item_ << std::endl;
  } else {
    std::cout << "right : "
              << "NULL" << std::endl;
  }
  if (node->parent) {
    std::cout << "parent: " << node->parent->item_ << std::endl;
  } else {
    std::cout << "parent: "
              << "NULL" << std::endl;
  }
  std::cout << std::endl;
}

template < typename T >
void pre_order_print(Node< T > *node) {
  if (!node) {
    return;
  }
  print_node(node);
  pre_order_print(node->left);
  pre_order_print(node->right);
}

template < typename T >
void in_order_print(Node< T > *node) {
  if (!node) {
    return;
  }
  in_order_print(node->left);
  print_node(node);
  in_order_print(node->right);
}

template < typename T >
void post_order_print(Node< T > *node) {
  if (!node) {
    return;
  }
  post_order_print(node->left);
  post_order_print(node->right);
  print_node(node);
}

template < typename T >
void destroy_node(Node< T > *node) {
  if (node) {
    destroy_node(node->left);
    destroy_node(node->right);
    delete node;
  }
}

// Node *search_node(double x, Node *node) {
//   while (node) {
//     if (node->item_ == x) {
//       return node;
//     } else if (x < node->item_) {
//       node = node->left;
//     } else {
//       node = node->right;
//     }
//   }
//   return NULL;
// }

template < typename T >
class BinarySearchTree {
 public:
  BinarySearchTree() : root_(NULL), n_(0) {}
  ~BinarySearchTree() {
    std::cout << "size:" << size(root_) << std::endl;
    destroy_node(root_);
  }

  Node< T > *search(T x) {
    Node< T > *tmp = root_;
    while (tmp) {
      if (tmp->item_ == x) {
        return tmp;
      } else if (x < tmp->item_) {
        tmp = tmp->left;
      } else {
        tmp = tmp->right;
      }
    }
    return NULL;
  }

  bool add(T x) {
    Node< T > *parent = find_last(x);
    Node< T > *child = new Node< T >(x);

    bool result = add_child(parent, child);
    if (!result) {
      delete child;
    }
    return result;
  }

  Node< T > *find_last(T x) {
    Node< T > *current = root_;
    Node< T > *prev = NULL;
    while (current) {
      prev = current;
      if (current->item_ == x) {
        return current;
      } else if (x < current->item_) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return prev;
  }

  bool add_child(Node< T > *parent, Node< T > *child) {
    if (!parent) {
      root_ = child;
    } else {
      if (child->item_ == parent->item_) {
        return false;
      } else if (child->item_ < parent->item_) {
        parent->left = child;
      } else {
        parent->right = child;
      }
      child->parent = parent;
    }
    n_++;
    return true;
  }

  void print_all() {
    in_order_print(root_);
    ;
  }

  void remove(Node< T > *node) {
    if (!node) {
      return;
    }
    if (!node->left || !node->right) {
      splice(node);
      delete node;
    } else {
      Node< T > *w = node->right;
      while (w->left) {
        w = w->left;
      }
      node->item_ = w->item_;
      splice(w);
      delete w;
    }
  }

  void splice(Node< T > *node) {
    Node< T > *s;
    Node< T > *p;

    if (!node) {
      return;
    }
    if (node->left) {
      s = node->left;
    } else {
      s = node->right;
    }

    if (node == root_) {
      root_ = s;
      p = NULL;
    } else {
      p = node->parent;
      if (p->left == node) {
        p->left = s;
      } else {
        p->right = s;
      }
    }

    if (s) {
      s->parent = p;
    }
    n_--;
  }

  Node< T > *root() const { return root_; }

 private:
  Node< T > *root_;
  int n_;
};

#endif /* TREE_HPP */
