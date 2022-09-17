#ifndef TREE_HPP
#define TREE_HPP

#include <algorithm>

struct Node {
  Node(double item = 0) : left(NULL), right(NULL), parent(NULL), item_(item) {}

  Node *left;
  Node *right;
  Node *parent;
  double item_;
};

int depth(Node *node) {
  int depth = 0;
  while (node) {
    node = node->parent;
    depth++;
  }
  return depth;
}

int size(Node *node) {
  if (!node) {
    return 0;
  }
  return 1 + size(node->left) + size(node->right);
}

int height(Node *node) {
  if (!node) {
    return -1;
  }
  return 1 + std::max(height(node->left), height(node->right));
}

void print_node(Node *node) {
  if (!node) {
    return;
  }
  std::cout << "node  : " << node << std::endl;
  std::cout << "item  : " << node->item_ << std::endl;
  std::cout << "left  : " << node->left << std::endl;
  std::cout << "right : " << node->right << std::endl;
  std::cout << "parent: " << node->parent << std::endl;
  std::cout << std::endl;
}

void traverse(Node *node) {
  if (!node) {
    return;
  }
  print_node(node);
  traverse(node->left);
  traverse(node->right);
}

void destroy_node(Node *node) {
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

class BinarySearchTree {
 public:
  BinarySearchTree() : root_(NULL), n_(0) {}
  ~BinarySearchTree() { destroy_node(root_); }

  Node *search(double x) {
    Node *tmp = root_;
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

  bool add(double x) {
    Node *parent = find_last(x);
    Node *child = new Node(x);
    // print_node(parent);
    // print_node(child);
    return add_child(parent, child);
  }

  Node *find_last(double x) {
    Node *current = root_;
    Node *prev = NULL;
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

  bool add_child(Node *parent, Node *child) {
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
    traverse(root_);
    ;
  }

  void remove(Node *node) {
    if (!node->left || !node->right) {
      splice(node);
      delete node;
    } else {
      Node *w = node->right;
      while (w->left) {
        w = w->left;
      }
      node->item_ = w->item_;
      splice(w);
      delete w;
    }
  }

  void splice(Node *node) {
    Node *s;
    Node *p;

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

  Node *root() const { return root_; }

 private:
  Node *root_;
  int n_;
};

#endif /* TREE_HPP */
