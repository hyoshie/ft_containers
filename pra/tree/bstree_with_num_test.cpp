#include <gtest/gtest.h>

#include "BSTreeWithNum.hpp"

class BSTreeWithNumTest : public ::testing::Test {
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
  BSTreeWithNum< int > btree;
  NodeWithNum< int > *root;
  NodeWithNum< int > *leaf;
};

TEST(NodeWithNumTest, BasicTest) {
  NodeWithNum< int > n_node;

  ASSERT_EQ(n_node.item, 0);
  ASSERT_EQ(n_node.left, nullptr);
  ASSERT_EQ(n_node.right, nullptr);
  ASSERT_EQ(n_node.pre_order_num, 0);
  ASSERT_EQ(n_node.in_order_num, 0);
  ASSERT_EQ(n_node.post_order_num, 0);
  ASSERT_TRUE(is_balanced(&n_node));
  ASSERT_EQ(size(&n_node), 1);
  ASSERT_EQ(height(&n_node), 0);
}

TEST_F(BSTreeWithNumTest, SizeTest) {
  ASSERT_EQ(size(root), 10);
  ASSERT_EQ(size(root->left), 4);
  ASSERT_EQ(size(btree.search(1)), 1);
  ASSERT_EQ(size(static_cast< NodeWithNum< int > * >(NULL)), 0);
}

TEST_F(BSTreeWithNumTest, PreOrderNumberTest) {
  btree.preOrderNumber(root);
  ASSERT_EQ(root->pre_order_num, 0);
  ASSERT_EQ(btree.search(1)->pre_order_num, 2);
  ASSERT_EQ(btree.search(2)->pre_order_num, 1);
  ASSERT_EQ(btree.search(3)->pre_order_num, 3);
  ASSERT_EQ(btree.search(4)->pre_order_num, 4);
  ASSERT_EQ(btree.search(5)->pre_order_num, 0);
  ASSERT_EQ(btree.search(6)->pre_order_num, 7);
  ASSERT_EQ(btree.search(7)->pre_order_num, 6);
  ASSERT_EQ(btree.search(8)->pre_order_num, 5);
  ASSERT_EQ(btree.search(9)->pre_order_num, 9);
  ASSERT_EQ(btree.search(10)->pre_order_num, 8);
}

TEST_F(BSTreeWithNumTest, InOrderNumberTest) {
  btree.inOrderNumber(root);
  ASSERT_EQ(root->in_order_num, 4);
  ASSERT_EQ(btree.search(1)->in_order_num, 0);
  ASSERT_EQ(btree.search(2)->in_order_num, 1);
  ASSERT_EQ(btree.search(3)->in_order_num, 2);
  ASSERT_EQ(btree.search(4)->in_order_num, 3);
  ASSERT_EQ(btree.search(5)->in_order_num, 4);
  ASSERT_EQ(btree.search(6)->in_order_num, 5);
  ASSERT_EQ(btree.search(7)->in_order_num, 6);
  ASSERT_EQ(btree.search(8)->in_order_num, 7);
  ASSERT_EQ(btree.search(9)->in_order_num, 8);
  ASSERT_EQ(btree.search(10)->in_order_num, 9);
}

TEST_F(BSTreeWithNumTest, PostOrderNumberTest) {
  btree.postOrderNumber(root);
  ASSERT_EQ(root->post_order_num, 9);
  ASSERT_EQ(btree.search(1)->post_order_num, 0);
  ASSERT_EQ(btree.search(2)->post_order_num, 3);
  ASSERT_EQ(btree.search(3)->post_order_num, 2);
  ASSERT_EQ(btree.search(4)->post_order_num, 1);
  ASSERT_EQ(btree.search(5)->post_order_num, 9);
  ASSERT_EQ(btree.search(6)->post_order_num, 4);
  ASSERT_EQ(btree.search(7)->post_order_num, 5);
  ASSERT_EQ(btree.search(8)->post_order_num, 8);
  ASSERT_EQ(btree.search(9)->post_order_num, 6);
  ASSERT_EQ(btree.search(10)->post_order_num, 7);
}

template < typename T >
void assert_2sizefunc_equal(NodeWithNum< T > *node) {
  ASSERT_EQ(size(node), size_from_order_num(node));
}

TEST_F(BSTreeWithNumTest, SizeFromOrderNumTest) {
  btree.preOrderNumber(root);
  btree.inOrderNumber(root);
  btree.postOrderNumber(root);
  assert_2sizefunc_equal(btree.search(1));
  assert_2sizefunc_equal(btree.search(2));
  assert_2sizefunc_equal(btree.search(3));
  assert_2sizefunc_equal(btree.search(4));
  assert_2sizefunc_equal(btree.search(5));
  assert_2sizefunc_equal(btree.search(6));
  assert_2sizefunc_equal(btree.search(7));
  assert_2sizefunc_equal(btree.search(8));
  assert_2sizefunc_equal(btree.search(9));
  assert_2sizefunc_equal(btree.search(10));
}
