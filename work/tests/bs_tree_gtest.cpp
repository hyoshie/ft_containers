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
