#include <gtest/gtest.h>

#include "../includes/bs_tree.hpp"

typedef ft::pair< int, char > test_pair;
typedef bs_tree_node< test_pair > test_node;
typedef bs_tree< int, test_pair, std::less< int > > test_tree;
typedef test_tree::iterator test_itr;
typedef test_tree::const_iterator test_const_itr;
typedef test_tree::reverse_iterator test_rev_itr;
typedef test_tree::const_reverse_iterator test_const_rev_itr;

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

  ASSERT_EQ(empty.header()->left, nullptr);
  ASSERT_EQ(empty.header()->right, nullptr);
}

TEST_F(TreeTestF, MostLeftRightTest) {
  ASSERT_EQ(tree.mostLeft()->item.first, -5);
  ASSERT_EQ(tree.mostRight()->item.first, 15);
  tree.remove(test_pair(-5, 'f'));
  tree.remove(test_pair(15, 'b'));
  ASSERT_EQ(tree.mostLeft()->item.first, -1);
  ASSERT_EQ(tree.mostRight()->item.first, 10);
}

TEST_F(TreeTestF, FindEqualTest) {
  test_node *node_m5 = tree.find_equal(-5);
  test_node *node_m1 = tree.find_equal(-1);
  test_node *node_0 = tree.find_equal(0);
  test_node *node_1 = tree.root();
  test_node *node_10 = tree.find_equal(10);
  test_node *node_15 = tree.find_equal(15);
  test_node *node_null = tree.find_equal(4242);
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
  ASSERT_EQ(tree.next(header), header);
}

TEST(TreeTest, NextTestWithSize0) {
  test_tree tree;
  test_node *root = tree.root();
  test_node *header = tree.header();
  // segv 、header->parentはデフォルトでnullのため
  // mapのメソッド実行時に確認する
  // test_node *root_next = tree.next(root);
}

TEST(TreeTest, NextTestWithSize1) {
  test_tree tree;
  tree.add(test_pair(1, 'a'));

  test_node *node_1 = tree.root();
  test_node *header = tree.header();

  ASSERT_EQ(tree.next(node_1), header);
}

TEST_F(TreeTestF, PrevTest) {
  test_node *node_m5 = tree.find_equal(-5);
  test_node *node_m1 = tree.find_equal(-1);
  test_node *node_0 = tree.find_equal(0);
  test_node *node_1 = tree.root();
  test_node *node_10 = tree.find_equal(10);
  test_node *node_15 = tree.find_equal(15);
  test_node *header = tree.header();

  ASSERT_EQ(tree.prev(node_m1)->item.second, node_m5->item.second);
  ASSERT_EQ(tree.prev(node_0)->item.second, node_m1->item.second);
  ASSERT_EQ(tree.prev(node_1)->item.second, node_0->item.second);
  ASSERT_EQ(tree.prev(node_10)->item.second, node_1->item.second);
  ASSERT_EQ(tree.prev(node_15)->item.second, node_10->item.second);
  ASSERT_EQ(tree.prev(header)->item.second, node_15->item.second);
  // beginのprev
  ASSERT_EQ(tree.prev(node_m5)->item.second, header->item.second);
}

TEST(TreeTest, PrevTestWithSize0) {
  test_tree tree;
  test_node *root = tree.root();
  test_node *header = tree.header();
  // segv
  // mapのメソッド実行時に確認する
  // test_node *root_prev = tree.prev(root);
}

TEST(TreeTest, PrevTestWithSize1) {
  test_tree tree;
  tree.add(test_pair(1, 'a'));

  test_node *node_1 = tree.root();
  test_node *header = tree.header();

  ASSERT_EQ(tree.prev(node_1), header);
}

TEST_F(TreeTestF, BeginTest) {
  test_itr it = tree.begin();
  test_const_itr c_it = tree.begin();
  test_node *node_m5 = tree.find_equal(-5);
  ASSERT_EQ(*it, node_m5->item);
  ASSERT_EQ(*c_it, node_m5->item);
  // *c_it = node_m5->item;
}

TEST_F(TreeTestF, RBeginTest) {
  test_rev_itr it = tree.rbegin();
  test_const_rev_itr c_it = tree.rbegin();
  test_node *node_15 = tree.find_equal(15);
  ASSERT_EQ(*it, node_15->item);
  ASSERT_EQ(*c_it, node_15->item);
}

TEST_F(TreeTestF, EndTest) {
  test_itr it = tree.end();
  test_const_itr c_it = tree.end();
  test_node *header = tree.header();
  ASSERT_EQ(*it, header->item);
  ASSERT_EQ(*c_it, header->item);
}

TEST_F(TreeTestF, REndTest) {
  test_rev_itr it = tree.rend();
  test_const_rev_itr c_it = tree.rend();
  --it;
  --c_it;
  test_node *node_15 = tree.find_equal(-5);
  ASSERT_EQ(*it, node_15->item);
  ASSERT_EQ(*c_it, node_15->item);
}

TEST_F(TreeTestF, IteratorArrowOperatorTest) {
  test_itr it = tree.begin();
  test_node *node_m5 = tree.find_equal(-5);
  ASSERT_EQ(it->first, node_m5->item.first);
}

TEST_F(TreeTestF, IteratorIncrementTest) {
  test_itr it = tree.begin();
  test_node *node_m1 = tree.find_equal(-1);
  test_node *node_0 = tree.find_equal(0);
  ++it;
  ASSERT_EQ(*it, node_m1->item);
  it++;
  ASSERT_EQ(*it, node_0->item);

  test_itr def_it;
  ++it;
  it++;
  *it;
}

TEST_F(TreeTestF, IteratorDecrementTest) {
  test_itr it = tree.end();
  test_node *header = tree.header();
  test_node *node_10 = tree.find_equal(10);
  test_node *node_15 = tree.find_equal(15);
  --it;
  ASSERT_EQ(*it, node_15->item);
  it--;
  ASSERT_EQ(*it, node_10->item);

  test_itr def_it;
  --it;
  it--;
  *it;
}

TEST_F(TreeTestF, IteratorPrintTest) {
  testing::internal::CaptureStdout();
  for (test_itr it = tree.begin(); it != tree.end(); it++) {
    std::cout << it->first << ", ";
  }
  ASSERT_STREQ("-5, -1, 0, 1, 10, 15, ",
               testing::internal::GetCapturedStdout().c_str());
}

TEST_F(TreeTestF, ReverseIteratorPrintTest) {
  testing::internal::CaptureStdout();
  for (test_rev_itr it = tree.rbegin(); it != tree.rend(); it++) {
    std::cout << it->first << ", ";
  }
  ASSERT_STREQ("15, 10, 1, 0, -1, -5, ",
               testing::internal::GetCapturedStdout().c_str());
}

TEST_F(TreeTestF, IteratorCompareOperatorTest) {
  test_itr it = tree.begin();
  test_itr copy(it);
  ASSERT_TRUE(it == copy);
  ASSERT_FALSE(it != copy);
  copy++;
  ASSERT_FALSE(it == copy);
  ASSERT_TRUE(it != copy);
}

TEST_F(TreeTestF, ConstIteratorCompareOperatorTest) {
  test_const_itr it = tree.begin();
  test_const_itr copy(it);
  ASSERT_TRUE(it == copy);
  ASSERT_FALSE(it != copy);
  it++;
  ASSERT_FALSE(it == copy);
  ASSERT_TRUE(it != copy);
}

TEST_F(TreeTestF, ConstIteratorPrintTest) {
  testing::internal::CaptureStdout();
  for (test_const_itr it = tree.begin(); it != tree.end(); it++) {
    std::cout << it->first << ", ";
  }
  ASSERT_STREQ("-5, -1, 0, 1, 10, 15, ",
               testing::internal::GetCapturedStdout().c_str());
}

TEST_F(TreeTestF, ConstReverseIteratorPrintTest) {
  testing::internal::CaptureStdout();
  for (test_const_rev_itr it = tree.rbegin(); it != tree.rend(); it++) {
    std::cout << it->first << ", ";
  }
  ASSERT_STREQ("15, 10, 1, 0, -1, -5, ",
               testing::internal::GetCapturedStdout().c_str());
}
TEST_F(TreeTestF, CompareIteratorAndConstIteratorTest) {
  test_itr it = tree.begin();
  test_const_itr c_it = tree.begin();
  ASSERT_TRUE(c_it == it);
  ASSERT_TRUE(it == c_it);
  ASSERT_FALSE(c_it != it);
  ASSERT_FALSE(it != c_it);
  it++;
  ASSERT_FALSE(c_it == it);
  ASSERT_FALSE(it == c_it);
  ASSERT_TRUE(c_it != it);
  ASSERT_TRUE(it != c_it);
}

TEST_F(TreeTestF, EmptyTest) {
  test_tree empty_tree;

  ASSERT_TRUE(empty_tree.empty());
  empty_tree.add(test_pair(1, 'a'));
  ASSERT_FALSE(empty_tree.empty());
  ASSERT_FALSE(tree.empty());
}

TEST_F(TreeTestF, SizeTest) {
  test_tree empty_tree;

  ASSERT_EQ(empty_tree.size(), 0);
  empty_tree.add(test_pair(1, 'a'));
  ASSERT_EQ(empty_tree.size(), 1);
  ASSERT_EQ(tree.size(), 6);
  // erase実装後テスト追加すること
}
