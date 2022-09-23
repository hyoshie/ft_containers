#include "BinarySearchTree.h"
#include "RedBlackTree.h"

static const int NUM = 10;

int main(void) {
  ods::RedBlackTree1< int > rbtree;

  for (int i = 0; i < NUM; i++) {
    rbtree.add(rand() % 1000);
  }
  rbtree.print();
  rbtree.verify();
  return 0;
}
