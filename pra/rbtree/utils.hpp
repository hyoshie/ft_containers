#ifndef UTILS_HPP
#define UTILS_HPP

template < typename NodeType >
int depth(NodeType *node) {
  int depth = 0;
  // node != root_
  while (node && node->parent) {
    node = node->parent;
    depth++;
  }
  return depth;
}

template < typename NodeType >
int size(NodeType *node) {
  if (!node) {
    return 0;
  }
  return 1 + size(node->left) + size(node->right);
}

template < typename NodeType >
int height(NodeType *node) {
  if (!node) {
    return -1;
  }
  return 1 + std::max(height(node->left), height(node->right));
}

// わかりにくい
template < typename NodeType >
bool has_travarsed(NodeType *node, NodeType *current, NodeType *prev) {
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

template < typename NodeType >
int size_no_recursive(NodeType *node) {
  if (!node) {
    return 0;
  }
  NodeType *current = node;
  NodeType *prev = node->parent;
  NodeType *next = NULL;
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

template < typename NodeType >
bool is_leaf(NodeType *node) {
  return (node && (!node->left && !node->right));
}

template < typename NodeType >
int height_no_recursive(NodeType *node) {
  if (!node) {
    return -1;
  }
  NodeType *current = node;
  NodeType *prev = node->parent;
  NodeType *next = NULL;
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

template < typename NodeType >
void print_node(NodeType *node) {
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

template < typename NodeType >
void print_node_graph(NodeType *node) {
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

template < typename NodeType >
void pre_order_print(NodeType *node) {
  if (!node) {
    return;
  }
  print_node(node);
  pre_order_print(node->left);
  pre_order_print(node->right);
}

template < typename NodeType >
void pre_order_print_nore(NodeType *node) {
  if (!node) {
    return;
  }
  NodeType *current = node;
  NodeType *prev = node->parent;
  NodeType *next = NULL;

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

template < typename NodeType >
void in_order_print(NodeType *node) {
  if (!node) {
    return;
  }
  in_order_print(node->left);
  print_node(node);
  in_order_print(node->right);
}

template < typename NodeType >
void in_order_print_nore(NodeType *node) {
  if (!node) {
    return;
  }
  NodeType *current = node;
  NodeType *prev = node->parent;
  NodeType *next = NULL;

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

template < typename NodeType >
void post_order_print(NodeType *node) {
  if (!node) {
    return;
  }
  post_order_print(node->left);
  post_order_print(node->right);
  print_node(node);
}

template < typename NodeType >
void post_order_print_nore(NodeType *node) {
  if (!node) {
    return;
  }
  NodeType *current = node;
  NodeType *prev = node->parent;
  NodeType *next = NULL;

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

template < typename NodeType >
void print_graph(NodeType *node, int depth) {
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

template < typename NodeType >
void destroy_node(NodeType *node) {
  if (node) {
    destroy_node(node->left);
    destroy_node(node->right);
    delete node;
  }
}

template < typename NodeType >
bool is_balanced(NodeType *node) {
  if (!node) {
    return true;
  }
  bool roughly_same = (std::abs(size(node->left) - size(node->right)) <= 1);

  return roughly_same && is_balanced(node->left) && is_balanced(node->right);
}

#endif /* UTILS_HPP */
