#ifndef TREE_HPP
#define TREE_HPP

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <string>

template < typename T >
struct Node {
  Node(T given = 0) : left(NULL), right(NULL), parent(NULL), item(given) {}

  Node *left;
  Node *right;
  Node *parent;
  T item;
};

template < typename T >
int depth(Node< T > *node) {
  int depth = 0;
  // node != root_
  while (node && node->parent) {
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

// わかりにくい
template < typename T >
bool has_travarsed(Node< T > *node, Node< T > *current, Node< T > *prev) {
  if (current == node) {
    if (node->left && node->right) {
      return prev == node->right;
    } else if (node->left) {
      return prev == node->left;
    } else if (node->right) {
      return prev == node->right;
    } else {
      return false;
    }
  } else {
    return !node->left && !node->right;
  }
  // if (node->left && node->right) {
  //   return current == node && prev == node->right;
  // } else if (node->left) {
  //   return current == node && prev == node->left;
  // } else if (node->right) {
  //   return current == node && prev == node->right;
  // } else {
  //   return current != node;
  // }
  // // 通らない
  // assert(0);
  // return false;
}

template < typename T >
int size_no_recursive(Node< T > *node) {
  if (!node) {
    return 0;
  }
  Node< T > *current = node;
  Node< T > *prev = node->parent;
  Node< T > *next = NULL;
  int size = 0;

  while (current && !has_travarsed(node, current, prev)) {
    if (prev == current->parent) {
      // 新しいノードを訪問したとき
      size++;
      if (current->left) {
        next = current->left;
      } else if (current->right) {
        next = current->right;
      } else {
        next = current->parent;
      }
    } else if (prev == current->left) {
      // 左の子を訪問して戻ってきたとき
      if (current->right) {
        next = current->right;
      } else {
        next = current->parent;
      }
    } else {
      // 訪問済みのノードを遡る
      next = current->parent;
    }
    prev = current;
    current = next;
  }
  return size;
}

template < typename T >
bool is_leaf(Node< T > *node) {
  return (node && (!node->left && !node->right));
}

template < typename T >
int height_no_recursive(Node< T > *node) {
  if (!node) {
    return -1;
  }
  Node< T > *current = node;
  Node< T > *prev = node->parent;
  Node< T > *next = NULL;
  int height = 0;
  int tmp_height = 0;

  while (current && !has_travarsed(node, current, prev)) {
    if (prev == current->parent) {
      // 新しいノードを訪問したとき
      if (is_leaf(current)) {
        height = std::max(tmp_height, height);
      }
      if (current->left) {
        next = current->left;
        tmp_height++;
      } else if (current->right) {
        next = current->right;
        tmp_height++;
      } else {
        next = current->parent;
        tmp_height--;
      }
    } else if (prev == current->left) {
      // 左の子を訪問して戻ってきたとき
      if (current->right) {
        next = current->right;
        tmp_height++;
      } else {
        next = current->parent;
        tmp_height--;
      }
    } else {
      // 訪問済みのノードを遡る
      next = current->parent;
      tmp_height--;
    }
    prev = current;
    current = next;
  }
  return height;
}

template < typename T >
void print_node(Node< T > *node) {
  if (!node) {
    return;
  }

  std::string node_item = std::to_string(node->item);
  std::string parent_item =
      (node->parent) ? std::to_string(node->parent->item) : "NULL";
  std::string left_item =
      (node->left) ? std::to_string(node->left->item) : "NULL";
  std::string right_item =
      (node->right) ? std::to_string(node->right->item) : "NULL";

  std::cout << "item  : " << node_item << std::endl
            << "left  : " << left_item << std::endl
            << "right : " << right_item << std::endl
            << "parent: " << parent_item << std::endl
            << std::endl;
}

template < typename T >
void print_node_graph(Node< T > *node) {
  if (!node) {
    return;
  }

  std::string node_item = std::to_string(node->item);
  std::string parent_item =
      (node->parent) ? std::to_string(node->parent->item) : "    NULL";
  std::string left_item =
      (node->left) ? std::to_string(node->left->item) : "NULL";
  std::string right_item =
      (node->right) ? std::to_string(node->right->item) : "NULL";

  std::cout << std::setw(6) << parent_item << std::endl;
  std::cout << "     |        " << std::endl;
  std::cout << std::setw(6) << node_item << std::endl;
  std::cout << "   /   \\     " << std::endl;
  std::cout << std::setw(3) << left_item << "     " << right_item << std::endl;
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
void pre_order_print_nore(Node< T > *node) {
  if (!node) {
    return;
  }
  Node< T > *current = node;
  Node< T > *prev = node->parent;
  Node< T > *next = NULL;

  while (current && !has_travarsed(node, current, prev)) {
    if (prev == current->parent) {
      // 新しいノードを訪問したとき
      print_node(current);
      if (current->left) {
        next = current->left;
      } else if (current->right) {
        next = current->right;
      } else {
        next = current->parent;
      }
    } else if (prev == current->left) {
      // 左の子を訪問して戻ってきたとき
      if (current->right) {
        next = current->right;
      } else {
        next = current->parent;
      }
    } else {
      // 訪問済みのノードを遡る
      next = current->parent;
    }
    prev = current;
    current = next;
  }
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
void in_order_print_nore(Node< T > *node) {
  if (!node) {
    return;
  }
  Node< T > *current = node;
  Node< T > *prev = node->parent;
  Node< T > *next = NULL;

  // std::cout << std::endl;
  while (current && !has_travarsed(node, current, prev)) {
    if (prev == current->parent) {
      // 新しいノードを訪問したとき
      if (current->left) {
        next = current->left;
      } else if (current->right) {
        print_node(current);
        next = current->right;
      } else {
        print_node(current);
        next = current->parent;
      }
    } else if (prev == current->left) {
      // 左の子を訪問して戻ってきたとき
      print_node(current);
      if (current->right) {
        next = current->right;
      } else {
        next = current->parent;
      }
    } else {
      // 訪問済みのノードを遡る
      next = current->parent;
    }
    prev = current;
    current = next;
  }
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
void post_order_print_nore(Node< T > *node) {
  if (!node) {
    return;
  }
  Node< T > *current = node;
  Node< T > *prev = node->parent;
  Node< T > *next = NULL;

  while (current && !has_travarsed(node, current, prev)) {
    if (prev == current->parent) {
      // 新しいノードを訪問したとき
      if (current->left) {
        next = current->left;
      } else if (current->right) {
        next = current->right;
      } else {
        print_node(current);
        next = current->parent;
      }
    } else if (prev == current->left) {
      // 左の子を訪問して戻ってきたとき
      if (current->right) {
        next = current->right;
      } else {
        print_node(current);
        next = current->parent;
      }
    } else {
      // 訪問済みのノードを遡る
      print_node(current);
      next = current->parent;
    }
    prev = current;
    current = next;
  }
  print_node(node);
}

template < typename T >
void print_graph(Node< T > *node, int depth) {
  if (!node) {
    return;
  }

  print_graph(node->left, depth + 1);

  for (int i = 0; i < depth * 2; i++) {
    std::cout << " ";
  }
  std::cout << "+" << std::setw(2) << node->item << std::endl;

  print_graph(node->right, depth + 1);

  depth++;
}

template < typename T >
void destroy_node(Node< T > *node) {
  if (node) {
    destroy_node(node->left);
    destroy_node(node->right);
    delete node;
  }
}

template < typename T >
bool is_balanced(Node< T > *node) {
  if (!node) {
    return true;
  }
  bool roughly_same = (std::abs(size(node->left) - size(node->right)) <= 1);

  return roughly_same && is_balanced(node->left) && is_balanced(node->right);
}

template < typename T >
class BinarySearchTree {
 public:
  typedef Node< T > node_type;
  BinarySearchTree() : root_(NULL), n_(0) {}
  ~BinarySearchTree() { destroy_node(root_); }

  node_type *search(T x) {
    node_type *tmp = root_;
    while (tmp) {
      if (tmp->item == x) {
        return tmp;
      } else if (x < tmp->item) {
        tmp = tmp->left;
      } else {
        tmp = tmp->right;
      }
    }
    return NULL;
  }

  bool add(T x) {
    node_type *parent = find_last(x);
    node_type *child = new Node< T >(x);

    bool result = add_child(parent, child);
    if (!result) {
      delete child;
    }
    return result;
  }

  // xを保持しているノードを探す
  // 見つからないときは最後に出会ったノードを返す
  node_type *find_last(T x) {
    node_type *current = root_;
    node_type *prev = NULL;
    while (current) {
      prev = current;
      if (current->item == x) {
        return current;
      } else if (x < current->item) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return prev;
  }

  bool add_child(node_type *parent, Node< T > *child) {
    if (!parent) {
      root_ = child;
    } else {
      if (child->item == parent->item) {
        return false;
      } else if (child->item < parent->item) {
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

  void remove(node_type *node) {
    if (!node) {
      return;
    }
    if (!node->left || !node->right) {
      // 葉か子を1つ持つノードのとき
      splice(node);
      delete node;
    } else {
      // 子を2つ持つノードのとき
      // node->rightを根とする部分木の最小値を保持するノードを見つける
      // そのノードとnodeの値を交換する
      // そのノードを削除する
      node_type *w = node->right;
      while (w->left) {
        w = w->left;
      }
      node->item = w->item;
      splice(w);
      delete w;
    }
  }

  // ノードを木から削除する
  // 葉のとき->ノードを親から切り離す
  // 子を1つ持つノードのとき->ノードを親から切り離す
  void splice(node_type *node) {
    node_type *grandchild;
    node_type *parent;

    if (!node) {
      return;
    }

    // 子を1つ持つノードのとき
    if (node->left) {
      grandchild = node->left;
    } else {
      grandchild = node->right;
    }

    if (node == root_) {
      // 根を削除するとき
      root_ = grandchild;
      parent = NULL;
    } else {
      // 根以外のノードを削除するとき
      parent = node->parent;
      if (parent->left == node) {
        // ノードがその親の左の子のとき
        parent->left = grandchild;
      } else {
        // ノードがその親の右の子のとき
        parent->right = grandchild;
      }
    }

    // 葉でないときは親とつなげる
    if (grandchild) {
      grandchild->parent = parent;
    }
    n_--;
  }

  node_type *root() const { return root_; }

 private:
  node_type *root_;
  int n_;
};

#endif /* TREE_HPP */
