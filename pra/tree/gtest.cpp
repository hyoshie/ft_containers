#include <gtest/gtest.h>

#include "BinarySearchTree.hpp"

class BSTTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    int array[] = {5, 8, 2, 7, 10, 9, 3, 6, 4, 1};

    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
      btree.add(array[i]);
    }
    root = btree.root();
    leaf = btree.search(1);
  }
  virtual void TearDown() {}
  BinarySearchTree< int > btree;
  Node< int > *root;
  Node< int > *leaf;
};

template < typename T >
void assert_2sizefunc_equal(Node< T > *node) {
  ASSERT_EQ(size(node), size_no_recursive(node));
}

template < typename T >
void assert_2heightfunc_equal(Node< T > *node) {
  ASSERT_EQ(height(node), height_no_recursive(node));
}

TEST_F(BSTTest, SizeTest) {
  ASSERT_EQ(size(root), 10);
  ASSERT_EQ(size(root->left), 4);
  ASSERT_EQ(size(btree.search(1)), 1);
  ASSERT_EQ(size(static_cast< Node< int > * >(NULL)), 0);
}

TEST_F(BSTTest, SizeNoRecursiveTest) {
  assert_2sizefunc_equal(root);
  assert_2sizefunc_equal(root->left);
  assert_2sizefunc_equal(root->right);
  assert_2sizefunc_equal(leaf);
  assert_2sizefunc_equal(static_cast< Node< int > * >(NULL));
}

TEST_F(BSTTest, HeightTest) {
  ASSERT_EQ(height(static_cast< Node< int > * >(NULL)), -1);
  ASSERT_EQ(height(root), 3);
  ASSERT_EQ(height(root->left), 2);
  ASSERT_EQ(height(leaf), 0);
}

TEST_F(BSTTest, HeightNoRecursiveTest) {
  assert_2heightfunc_equal(root);
  assert_2heightfunc_equal(root->left);
  assert_2heightfunc_equal(root->right);
  assert_2heightfunc_equal(leaf);
  assert_2heightfunc_equal(static_cast< Node< int > * >(NULL));
}

TEST_F(BSTTest, IsBalancedTest) {
  BinarySearchTree< int > unbalanced;
  int array[] = {2, 9, 8, 7, 10, 6, 3, 5, 4, 1};
  for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
    unbalanced.add(array[i]);
  }
  Node< int > *u_root = unbalanced.root();
  Node< int > *u_leaf = unbalanced.search(1);
  ASSERT_EQ(u_leaf->item, 1);
  ASSERT_EQ(is_balanced(u_root), false);
  ASSERT_EQ(is_balanced(u_leaf), true);
  ASSERT_EQ(is_balanced(unbalanced.search(5)), true);
  ASSERT_EQ(is_balanced(unbalanced.search(3)), false);
  ASSERT_EQ(is_balanced(root), true);
  ASSERT_EQ(is_balanced(leaf), true);
}
