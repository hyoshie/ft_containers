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
    node_nil = tree.nil();
    node_1st = tree.find_equal(-5);
    node_2nd = tree.find_equal(-1);
    node_3rd = tree.find_equal(0);
    node_4th = tree.find_equal(1);
    node_5th = tree.find_equal(10);
    node_6th = tree.find_equal(15);
    node_header = tree.header();
  }
  virtual void TearDown() {}

  test_tree tree;
  test_node *node_nil;
  test_node *node_1st;
  test_node *node_2nd;
  test_node *node_3rd;
  test_node *node_4th;
  test_node *node_5th;
  test_node *node_6th;
  test_node *node_header;
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
  // 現在true。引数を後で考える
  // ASSERT_FALSE(tree.remove(test_pair(15, 'z')));
  // tree.print();
}

TEST(TreeTest, HeaderEmptyTest) {
  test_tree empty;

  ASSERT_EQ(empty.header()->left, nullptr);
  ASSERT_EQ(empty.header()->right, nullptr);
}

// TEST_F(TreeTestF, MostLeftRightTest) {
//   ASSERT_EQ(tree.mostLeft()->item.first, -5);
//   ASSERT_EQ(tree.mostRight()->item.first, 15);
//   tree.remove(test_pair(-5, 'f'));
//   tree.remove(test_pair(15, 'b'));
//   ASSERT_EQ(tree.mostLeft()->item.first, -1);
//   ASSERT_EQ(tree.mostRight()->item.first, 10);
// }

TEST_F(TreeTestF, FindEqualTest) {
  test_node *node_null = tree.find_equal(4242);
  ASSERT_EQ(node_1st->item.second, 'f');
  ASSERT_EQ(node_2nd->item.second, 'c');
  ASSERT_EQ(node_3rd->item.second, 'e');
  ASSERT_EQ(node_4th->item.second, 'a');
  ASSERT_EQ(node_5th->item.second, 'd');
  ASSERT_EQ(node_6th->item.second, 'b');
  ASSERT_EQ(node_null, nullptr);
}

TEST_F(TreeTestF, NextTest) {
  tree.print();
  ASSERT_EQ(next(node_1st, node_nil)->item.second, node_2nd->item.second);
  ASSERT_EQ(next(node_2nd, node_nil)->item.second, node_3rd->item.second);
  ASSERT_EQ(next(node_3rd, node_nil)->item.second, node_4th->item.second);
  ASSERT_EQ(next(node_4th, node_nil)->item.second, node_5th->item.second);
  ASSERT_EQ(next(node_5th, node_nil)->item.second, node_6th->item.second);
  ASSERT_EQ(next(node_6th, node_nil), node_header);
  ASSERT_EQ(next(node_header, node_nil), node_header);
}

TEST(TreeTest, NextTestWithSize0) {
  test_tree tree;
  test_node *root = tree.root();
  test_node *node_header = tree.header();
  // segv 、node_header->parentはデフォルトでnullのため
  // mapのメソッド実行時に確認する
  // test_node *root_next = tree.next(root);
}

TEST(TreeTest, NextTestWithSize1) {
  test_tree tree;
  tree.add(test_pair(1, 'a'));

  test_node *node_4th = tree.root();
  test_node *node_header = tree.header();
  test_node *node_nil = tree.nil();

  ASSERT_EQ(next(node_4th, node_nil), node_header);
}

TEST_F(TreeTestF, PrevTest) {
  ASSERT_EQ(prev(node_2nd, node_nil)->item.second, node_1st->item.second);
  ASSERT_EQ(prev(node_3rd, node_nil)->item.second, node_2nd->item.second);
  ASSERT_EQ(prev(node_4th, node_nil)->item.second, node_3rd->item.second);
  ASSERT_EQ(prev(node_5th, node_nil)->item.second, node_4th->item.second);
  ASSERT_EQ(prev(node_6th, node_nil)->item.second, node_5th->item.second);
  ASSERT_EQ(prev(node_header, node_nil)->item.second, node_6th->item.second);
  // beginのprev
  ASSERT_EQ(prev(node_1st, node_nil)->item.second, node_header->item.second);
}

TEST(TreeTest, PrevTestWithSize0) {
  test_tree tree;
  test_node *root = tree.root();
  test_node *node_header = tree.header();
  // segv
  // mapのメソッド実行時に確認する
  // test_node *root_prev = tree.prev(root);
}

TEST(TreeTest, PrevTestWithSize1) {
  test_tree tree;
  tree.add(test_pair(1, 'a'));

  test_node *node_4th = tree.root();
  test_node *node_header = tree.header();
  test_node *node_nil = tree.nil();

  ASSERT_EQ(prev(node_4th, node_nil), node_header);
}

TEST_F(TreeTestF, BeginTest) {
  test_itr it = tree.begin();
  test_const_itr c_it = tree.begin();
  ASSERT_EQ(*it, node_1st->item);
  ASSERT_EQ(*c_it, node_1st->item);
  // *c_it = node_1st->item;
}

TEST_F(TreeTestF, RBeginTest) {
  test_rev_itr it = tree.rbegin();
  test_const_rev_itr c_it = tree.rbegin();
  ASSERT_EQ(*it, node_6th->item);
  ASSERT_EQ(*c_it, node_6th->item);
}

TEST_F(TreeTestF, EndTest) {
  test_itr it = tree.end();
  test_const_itr c_it = tree.end();
  ASSERT_EQ(*it, node_header->item);
  ASSERT_EQ(*c_it, node_header->item);
}

TEST_F(TreeTestF, REndTest) {
  test_rev_itr it = tree.rend();
  test_const_rev_itr c_it = tree.rend();
  --it;
  --c_it;
  ASSERT_EQ(*it, node_1st->item);
  ASSERT_EQ(*c_it, node_1st->item);
}

TEST_F(TreeTestF, IteratorArrowOperatorTest) {
  test_itr it = tree.begin();
  ASSERT_EQ(it->first, node_1st->item.first);
}

TEST_F(TreeTestF, IteratorIncrementTest) {
  test_itr it = tree.begin();
  ++it;
  ASSERT_EQ(*it, node_2nd->item);
  it++;
  ASSERT_EQ(*it, node_3rd->item);

  test_itr def_it;
  ++it;
  it++;
  *it;
}

TEST_F(TreeTestF, IteratorDecrementTest) {
  test_itr it = tree.end();
  --it;
  ASSERT_EQ(*it, node_6th->item);
  it--;
  ASSERT_EQ(*it, node_5th->item);

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

TEST_F(TreeTestF, Insert1FailTest) {
  test_pair dup_key_pair(1, 'z');
  ft::pair< test_itr, bool > failed = tree.insert(dup_key_pair);
  ASSERT_FALSE(failed.second);
  test_itr disrupted = failed.first;
  ASSERT_EQ(disrupted->first, 1);
  ASSERT_EQ(disrupted->second, 'a');
  disrupted--;
  ASSERT_EQ(disrupted, test_itr(node_3rd, node_nil));
  ASSERT_EQ(failed, ft::make_pair(test_itr(node_4th, node_nil), false));
}

TEST_F(TreeTestF, Insert1SuccessTest) {
  test_pair original_key_pair(42, 'z');
  ft::pair< test_itr, bool > success = tree.insert(original_key_pair);
  ASSERT_TRUE(success.second);
  test_itr inserted = success.first;
  ASSERT_EQ(inserted->first, 42);
  ASSERT_EQ(inserted->second, 'z');
  inserted--;
  ASSERT_EQ(inserted, test_itr(node_6th, node_nil));
}

TEST_F(TreeTestF, InsertHintFailTest) {
  test_pair dup_key_pair(1, 'z');
  test_itr it = tree.begin();
  test_itr disrupted = tree.insert(it, dup_key_pair);
  ASSERT_EQ(disrupted->first, 1);
  ASSERT_EQ(disrupted->second, 'a');
  disrupted--;
  ASSERT_EQ(disrupted, test_itr(node_3rd, node_nil));
}

TEST_F(TreeTestF, InsertHintSuccessTest) {
  test_pair original_key_pair(42, 'z');
  test_itr it = tree.begin();
  test_itr inserted = tree.insert(it, original_key_pair);
  ASSERT_EQ(inserted->first, 42);
  ASSERT_EQ(inserted->second, 'z');
  inserted--;
  ASSERT_EQ(inserted, test_itr(node_6th, node_nil));
}

TEST_F(TreeTestF, InsertRangeTest) {
  std::vector< test_pair > v;
  for (int i = 100; i < 110; i++) {
    v.push_back(test_pair(i, 'x'));
  }
  tree.insert(v.begin(), v.end());
  ASSERT_EQ(tree.size(), 16);
  for (int i = 100; i < 110; i++) {
    ASSERT_EQ(tree.find_equal(i)->item.second, 'x');
  }
}

TEST_F(TreeTestF, Erase1Test) {
  tree.erase(test_itr(node_3rd, node_nil));
  test_node *deleted = tree.find_equal(0);
  ASSERT_EQ(deleted, nullptr);
  ASSERT_EQ(tree.size(), 5);
}

TEST_F(TreeTestF, EraseKeySuccessTest) {
  test_tree::size_type ret = tree.erase(node_3rd->item.first);
  test_node *deleted = tree.find_equal(0);
  ASSERT_EQ(ret, 1);
  ASSERT_EQ(deleted, nullptr);
  ASSERT_EQ(tree.size(), 5);
}

TEST_F(TreeTestF, EraseKeyFailTest) {
  test_tree::size_type ret = tree.erase(42);
  ASSERT_EQ(ret, 0);
  ASSERT_EQ(tree.size(), 6);
}

TEST_F(TreeTestF, EraseRangeTwoElementTest) {
  test_itr itr_3rd(node_3rd, node_nil);  // 0
  test_itr itr_5th(node_5th, node_nil);  // 10
  tree.erase(itr_3rd, itr_5th);
  ASSERT_EQ(tree.size(), 4);
  tree.print();
}

TEST_F(TreeTestF, EraseRangeALLTest) {
  tree.erase(tree.begin(), tree.end());
  ASSERT_EQ(tree.size(), 0);
}
