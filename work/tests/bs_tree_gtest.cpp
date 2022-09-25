#include <gtest/gtest.h>

#include "../includes/bs_tree.hpp"

typedef std::pair< int, char > test_pair;
typedef bs_tree_node< test_pair > test_node;
typedef bs_tree< int, test_pair, std::less< int > > test_tree;

class TreeTestF : public ::testing::Test {
 protected:
  virtual void SetUp() {
    tree.add(test_pair(1, 'a'));
    tree.add(test_pair(15, 'b'));
    tree.add(test_pair(-1, 'c'));
    tree.add(test_pair(10, 'd'));
    tree.add(test_pair(0, 'e'));
    tree.add(test_pair(-5, 'f'));
  }
  virtual void TearDown() {}

  test_tree tree;
};

TEST(NodeTest, DefaultConstructTest) {
  bs_tree_node< int > def_node;
  ASSERT_EQ(def_node.parent, nullptr);
  ASSERT_EQ(def_node.left, nullptr);
  ASSERT_EQ(def_node.right, nullptr);
}

TEST(NodeTest, ConstructTest) {
  bs_tree_node< int > node(42);
  ASSERT_EQ(node.parent, nullptr);
  ASSERT_EQ(node.left, nullptr);
  ASSERT_EQ(node.right, nullptr);
  ASSERT_EQ(node.item, 42);
}

TEST(TreeTest, ConstructTest) {
  test_tree tree;
  ;
}

TEST(TreeTest, AddTest) {
  test_tree tree;
  ASSERT_TRUE(tree.add(test_pair(1, 'a')));
  ASSERT_TRUE(tree.add(test_pair(15, 'b')));
  ASSERT_TRUE(tree.add(test_pair(-1, 'c')));
  ASSERT_TRUE(tree.add(test_pair(10, 'd')));
  ASSERT_FALSE(tree.add(test_pair(10, 'e')));
  tree.print();
}

TEST(TreeTest, RemoveTest) {
  test_tree tree;
  ASSERT_FALSE(tree.remove(test_pair(10, 'd')));
  ASSERT_TRUE(tree.add(test_pair(1, 'a')));
  ASSERT_TRUE(tree.add(test_pair(15, 'b')));
  ASSERT_TRUE(tree.add(test_pair(-1, 'c')));
  ASSERT_TRUE(tree.add(test_pair(10, 'd')));
  ASSERT_TRUE(tree.remove(test_pair(10, 'd')));
  ASSERT_TRUE(tree.remove(test_pair(1, 'a')));
  ASSERT_FALSE(tree.remove(test_pair(1, 'a')));
  // ASSERT_FALSE(tree.remove(test_pair(15, 'z')));
  // 現在true。引数を後で考える
  // tree.print();
}

TEST(TreeTest, HeaderEmptyTest) {
  test_tree empty;

  ASSERT_EQ(empty.header()->left, empty.header());
  ASSERT_EQ(empty.header()->right, empty.header());
}

TEST_F(TreeTestF, HeaderTest) {
  ASSERT_EQ(tree.header()->left->item.first, -5);
  ASSERT_EQ(tree.header()->right->item.first, 15);
  tree.remove(test_pair(-5, 'f'));
  tree.remove(test_pair(15, 'b'));
  ASSERT_EQ(tree.header()->left->item.first, -1);
  ASSERT_EQ(tree.header()->right->item.first, 10);
}

TEST_F(TreeTestF, FindEqualTest) {
  bs_tree_node< test_pair > *node_m5 = tree.find_equal(-5);
  bs_tree_node< test_pair > *node_m1 = tree.find_equal(-1);
  bs_tree_node< test_pair > *node_0 = tree.find_equal(0);
  bs_tree_node< test_pair > *node_1 = tree.root();
  bs_tree_node< test_pair > *node_10 = tree.find_equal(10);
  bs_tree_node< test_pair > *node_15 = tree.find_equal(15);
  bs_tree_node< test_pair > *node_null = tree.find_equal(4242);
  ASSERT_EQ(node_m5->item.second, 'f');
  ASSERT_EQ(node_m1->item.second, 'c');
  ASSERT_EQ(node_0->item.second, 'e');
  ASSERT_EQ(node_1->item.second, 'a');
  ASSERT_EQ(node_10->item.second, 'd');
  ASSERT_EQ(node_15->item.second, 'b');
  ASSERT_EQ(node_null, nullptr);
}

TEST_F(TreeTestF, NextTest) {
  tree.print();
  test_node *node_m5 = tree.find_equal(-5);
  test_node *node_m1 = tree.find_equal(-1);
  test_node *node_0 = tree.find_equal(0);
  test_node *node_1 = tree.root();
  test_node *node_10 = tree.find_equal(10);
  test_node *node_15 = tree.find_equal(15);
  test_node *header = tree.header();

  ASSERT_EQ(tree.next(node_m5)->item.second, node_m1->item.second);
  ASSERT_EQ(tree.next(node_m1)->item.second, node_0->item.second);
  ASSERT_EQ(tree.next(node_0)->item.second, node_1->item.second);
  ASSERT_EQ(tree.next(node_1)->item.second, node_10->item.second);
  ASSERT_EQ(tree.next(node_10)->item.second, node_15->item.second);
  ASSERT_EQ(tree.next(node_15), header);
}

TEST(TreeTest, NextTestWithSize0) {
  test_tree tree;
  test_node *root = tree.root();
  test_node *header = tree.header();
  // segv 、header->parentはデフォルトでnullのため
  // mapのメソッド実行時に確認する
  // bs_tree_node< test_pair > *root_next = tree.next(root);
}

TEST(TreeTest, NextTestWithSize1) {
  test_tree tree;
  tree.add(test_pair(1, 'a'));

  test_node *node_1 = tree.root();
  test_node *header = tree.header();

  ASSERT_EQ(tree.next(node_1), header);
}

TEST_F(TreeTestF, PrevTest) {
  tree.print();
  test_node *node_m5 = tree.find_equal(-5);
  test_node *node_m1 = tree.find_equal(-1);
  test_node *node_0 = tree.find_equal(0);
  test_node *node_1 = tree.root();
  test_node *node_10 = tree.find_equal(10);
  test_node *node_15 = tree.find_equal(15);
  test_node *header = tree.header();

  // ASSERT_EQ(tree.prev(node_m5)->item.second, node_m1->item.second);
  ASSERT_EQ(tree.prev(node_m1)->item.second, node_m5->item.second);
  ASSERT_EQ(tree.prev(node_0)->item.second, node_m1->item.second);
  ASSERT_EQ(tree.prev(node_1)->item.second, node_0->item.second);
  ASSERT_EQ(tree.prev(node_10)->item.second, node_1->item.second);
  ASSERT_EQ(tree.prev(node_15)->item.second, node_10->item.second);
  // ASSERT_EQ(tree.prev(header)->item.second, node_15->item.second);
  // ASSERT_EQ(tree.prev(node_15), header);
}
