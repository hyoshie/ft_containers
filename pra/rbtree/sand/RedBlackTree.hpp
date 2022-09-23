#ifndef REDBRACKTREE_HPP
#define REDBRACKTREE_HPP

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <string>

#include "utils.hpp"

template < typename T >
struct Node {
  Node(T given = 0) : left(NULL), right(NULL), parent(NULL), item(given) {}

  Node *left;
  Node *right;
  Node *parent;
  T item;
  char color;
};

template < typename T >
class RedBlackTree {
 private:
  typedef Node< T > node_type;

 public:
  RedBlackTree() : root_(NULL), n_(0) {}
  ~RedBlackTree() { destroy_node(root_); }

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

  bool add_child(node_type *parent, node_type *child) {
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

  void rotate_left(node_type *node) {
    node_type *pivot = node->right;
    if (!pivot) {
      return;
    }
    pivot->parent = node->parent;
    // nodeの親の情報を更新
    if (pivot->parent) {
      if (pivot->parent->left == node) {
        pivot->parent->left = pivot;
      } else {
        pivot->parent->right = pivot;
      }
    }
    node->right = pivot->left;
    // nodeの右の子の情報を更新
    if (node->right) {
      node->right->parent = node;
    }
    node->parent = pivot;
    pivot->left = node;

    if (node == root_) {
      root_ = pivot;
      root_->parent = NULL;
    }
  }

  void rotate_right(node_type *node) {
    node_type *pivot = node->left;
    if (!pivot) {
      return;
    }
    pivot->parent = node->parent;
    // nodeの親の情報を更新
    if (pivot->parent) {
      if (pivot->parent->left == node) {
        pivot->parent->left = pivot;
      } else {
        pivot->parent->right = pivot;
      }
    }
    node->left = pivot->right;
    // nodeの右の子の情報を更新
    if (node->left) {
      node->left->parent = node;
    }
    node->parent = pivot;
    pivot->right = node;

    if (node == root_) {
      root_ = pivot;
      root_->parent = NULL;
    }
  }

  node_type *root() const { return root_; }

 protected:
  node_type *root_;
  int n_;
};

#endif /* REDBRACKTREE_HPP */
