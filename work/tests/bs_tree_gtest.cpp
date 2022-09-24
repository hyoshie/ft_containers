#include <gtest/gtest.h>

#include "../includes/bs_tree.hpp"

typedef std::pair< int, char > testpair;

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
  bs_tree< int, testpair, std::less< int > > tree;
  ;
}

TEST(TreeTest, AddTest) {
  bs_tree< int, testpair, std::less< int > > tree;
  ASSERT_TRUE(tree.add(testpair(1, 'a')));
  ASSERT_TRUE(tree.add(testpair(15, 'b')));
  ASSERT_TRUE(tree.add(testpair(-1, 'c')));
  ASSERT_TRUE(tree.add(testpair(10, 'd')));
  ASSERT_FALSE(tree.add(testpair(10, 'e')));
  tree.print();
}

TEST(TreeTest, RemoveTest) {
  bs_tree< int, testpair, std::less< int > > tree;
  ASSERT_FALSE(tree.remove(testpair(10, 'd')));
  ASSERT_TRUE(tree.add(testpair(1, 'a')));
  ASSERT_TRUE(tree.add(testpair(15, 'b')));
  ASSERT_TRUE(tree.add(testpair(-1, 'c')));
  ASSERT_TRUE(tree.add(testpair(10, 'd')));
  ASSERT_TRUE(tree.remove(testpair(10, 'd')));
  ASSERT_TRUE(tree.remove(testpair(1, 'a')));
  ASSERT_FALSE(tree.remove(testpair(1, 'a')));
  // ASSERT_FALSE(tree.remove(testpair(15, 'z')));
  // 現在true。引数を後で考える
  tree.print();
}

// TEST(TreeTest, MostLeftRightTest) {
//   bs_tree< int, testpair, std::less< int > > tree;
//   ASSERT_EQ(tree.most_left(), nullptr);
//   ASSERT_EQ(tree.most_right(), nullptr);
//   tree.add(testpair(1, 'a'));
//   tree.add(testpair(15, 'b'));
//   tree.add(testpair(-1, 'c'));
//   tree.add(testpair(10, 'd'));
//   tree.add(testpair(0, 'e'));
//   tree.add(testpair(-5, 'f'));
//   ASSERT_EQ(tree.most_left()->item.first, -5);
//   ASSERT_EQ(tree.most_right()->item.first, 15);
//   tree.print();
// }

TEST(TreeTest, HeaderTest) {
  bs_tree< int, testpair, std::less< int > > tree;

  ASSERT_EQ(tree.header()->left, nullptr);
  ASSERT_EQ(tree.header()->right, nullptr);
  tree.add(testpair(1, 'a'));
  tree.add(testpair(15, 'b'));
  tree.add(testpair(-1, 'c'));
  tree.add(testpair(10, 'd'));
  tree.add(testpair(0, 'e'));
  tree.add(testpair(-5, 'f'));
  ASSERT_EQ(tree.header()->left->item.first, -5);
  ASSERT_EQ(tree.header()->right->item.first, 15);
  tree.remove(testpair(-5, 'f'));
  tree.remove(testpair(15, 'b'));
  ASSERT_EQ(tree.header()->left->item.first, -1);
  ASSERT_EQ(tree.header()->right->item.first, 10);
  tree.print();
}
