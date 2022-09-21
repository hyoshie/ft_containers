#ifndef BSTREEWITHNUM_HPP
#define BSTREEWITHNUM_HPP

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <string>

#include "BinarySearchTree.hpp"

template < typename T >
struct NodeWithNum : public Node< T > {
  NodeWithNum(T given = 0)
      : Node< T >(given),
        pre_order_num(0),
        in_order_num(0),
        post_order_num(0) {}

  int pre_order_num;
  int in_order_num;
  int post_order_num;
};

template < typename T >
int size_from_order_num(NodeWithNum< T > *node) {
  if (is_leaf(node)) {
    return 1;
  }
  NodeWithNum< T > *left = static_cast< NodeWithNum< T > * >(node->left);
  NodeWithNum< T > *right = static_cast< NodeWithNum< T > * >(node->right);
  int right_subtree_size = (node->left)
                               ? node->post_order_num - left->post_order_num - 1
                               : node->post_order_num - right->post_order_num;
  int left_subtree_size = (node->right)
                              ? right->pre_order_num - node->pre_order_num - 1
                              : node->in_order_num - left->in_order_num;
  return right_subtree_size + left_subtree_size + 1;
}

template < typename T >
class BSTreeWithNum : public BinarySearchTree< T > {
 private:
  typedef NodeWithNum< T > node_type;

 public:
  BSTreeWithNum() : BinarySearchTree< T >() {}
  // ~BSTreeWithNum() { destroy_node(root_); }

  node_type *search(T x) {
    node_type *tmp = static_cast< node_type * >(BinarySearchTree< T >::root_);
    while (tmp) {
      if (tmp->item == x) {
        return tmp;
      } else if (x < tmp->item) {
        tmp = static_cast< node_type * >(tmp->left);
      } else {
        tmp = static_cast< node_type * >(tmp->right);
      }
    }
    return NULL;
  }

  bool add(T x) {
    node_type *parent =
        static_cast< node_type * >(BinarySearchTree< T >::find_last(x));
    node_type *child = new NodeWithNum< T >(x);

    bool result = BinarySearchTree< T >::add_child(parent, child);
    if (!result) {
      delete child;
    }
    return result;
  }

  bool add_child(node_type *parent, node_type *child) {
    if (!parent) {
      BinarySearchTree< T >::root_ = child;
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
    BinarySearchTree< T >::n_++;
    return true;
  }

  void preOrderNumber(node_type *node) {
    static int depth;
    if (!node) {
      return;
    }
    node->pre_order_num = depth++;
    preOrderNumber(static_cast< NodeWithNum< int > * >(node->left));
    preOrderNumber(static_cast< NodeWithNum< int > * >(node->right));
  }

  void inOrderNumber(node_type *node) {
    static int depth;
    if (!node) {
      return;
    }
    inOrderNumber(static_cast< NodeWithNum< int > * >(node->left));
    node->in_order_num = depth++;
    inOrderNumber(static_cast< NodeWithNum< int > * >(node->right));
  }

  void postOrderNumber(node_type *node) {
    static int depth;
    if (!node) {
      return;
    }
    postOrderNumber(static_cast< NodeWithNum< int > * >(node->left));
    postOrderNumber(static_cast< NodeWithNum< int > * >(node->right));
    node->post_order_num = depth++;
  }

  // node_type nextPreOrder(node_type *node) {
  //   ;
  //   return node;
  // }

  node_type *root() const {
    return static_cast< node_type * >(BinarySearchTree< T >::root_);
  }
};

#endif /* BSTREEWITHNUM_HPP */
