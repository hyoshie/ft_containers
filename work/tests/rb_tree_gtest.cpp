#include <gtest/gtest.h>

#include "../includes/rb_tree.hpp"

typedef ft::pair< int, char > test_pair;
typedef ft::rb_tree_node< test_pair > test_node;
typedef ft::rb_tree< int, test_pair, std::less< int > > test_tree;
typedef test_tree::iterator test_itr;
typedef test_tree::const_iterator test_const_itr;
typedef test_tree::reverse_iterator test_rev_itr;
typedef test_tree::const_reverse_iterator test_const_rev_itr;

class TreeTestF : public ::testing::Test {
 protected:
  virtual void SetUp() {
    tree.insert(test_pair(1, 'a'));
    tree.insert(test_pair(15, 'b'));
    tree.insert(test_pair(-1, 'c'));
    tree.insert(test_pair(10, 'd'));
    tree.insert(test_pair(0, 'e'));
    tree.insert(test_pair(-5, 'f'));
    tree.insert(test_pair(20, 'g'));
    tree.insert(test_pair(19, 'h'));
    tree.insert(test_pair(-3, 'i'));
    node_nil = tree.nil();
    node_1st_m5f = tree.find_equal(-5);
    node_2nd_m3i = tree.find_equal(-3);
    node_3rd_m1c = tree.find_equal(-1);
    node_4th_0e = tree.find_equal(0);
    node_5th_1a = tree.find_equal(1);
    node_6th_10d = tree.find_equal(10);
    node_7th_15b = tree.find_equal(15);
    node_8th_19g = tree.find_equal(19);
    node_last_20h = tree.find_equal(20);
    node_header = tree.header();
    default_size = tree.size();
  }
  virtual void TearDown() {}

  test_tree tree;
  test_node *node_nil;
  test_node *node_1st_m5f;
  test_node *node_2nd_m3i;
  test_node *node_3rd_m1c;
  test_node *node_4th_0e;
  test_node *node_5th_1a;
  test_node *node_6th_10d;
  test_node *node_7th_15b;
  test_node *node_8th_19g;
  test_node *node_last_20h;
  test_node *node_header;
  test_tree::size_type default_size;
};

TEST(NodeTest, DefaultConstructTest) {
  ft::rb_tree_node< int > def_node;
  ASSERT_EQ(def_node.parent, nullptr);
  ASSERT_EQ(def_node.left, nullptr);
  ASSERT_EQ(def_node.right, nullptr);
  ASSERT_EQ(def_node.color, 0);
  ASSERT_EQ(def_node.color, ft::red);
}

TEST(NodeTest, ConstructTest) {
  ft::rb_tree_node< int > node(42);
  ASSERT_EQ(node.parent, nullptr);
  ASSERT_EQ(node.left, nullptr);
  ASSERT_EQ(node.right, nullptr);
  ASSERT_EQ(node.item, 42);
}

TEST(TreeTest, ConstructTest) {
  test_tree tree;
  ;
}

TEST(TreeTest, HeaderEmptyTest) {
  test_tree empty;

  ASSERT_EQ(empty.header()->left, empty.nil());
  ASSERT_EQ(empty.header()->right, empty.nil());
}

TEST_F(TreeTestF, FindEqualTest) {
  test_node *node_null = tree.find_equal(4242);
  ASSERT_EQ(node_1st_m5f->item.second, 'f');
  ASSERT_EQ(node_2nd_m3i->item.second, 'i');
  ASSERT_EQ(node_3rd_m1c->item.second, 'c');
  ASSERT_EQ(node_4th_0e->item.second, 'e');
  ASSERT_EQ(node_5th_1a->item.second, 'a');
  ASSERT_EQ(node_6th_10d->item.second, 'd');
  ASSERT_EQ(node_null, node_nil);
}

TEST_F(TreeTestF, NextTest) {
  tree.print();
  ASSERT_EQ(next(node_1st_m5f, node_nil)->item.second,
            node_2nd_m3i->item.second);
  ASSERT_EQ(next(node_2nd_m3i, node_nil)->item.second,
            node_3rd_m1c->item.second);
  ASSERT_EQ(next(node_3rd_m1c, node_nil)->item.second,
            node_4th_0e->item.second);
  ASSERT_EQ(next(node_4th_0e, node_nil)->item.second, node_5th_1a->item.second);
  ASSERT_EQ(next(node_5th_1a, node_nil)->item.second,
            node_6th_10d->item.second);
  ASSERT_EQ(next(node_8th_19g, node_nil)->item.second,
            node_last_20h->item.second);
  ASSERT_EQ(next(node_last_20h, node_nil), node_header);
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
  tree.insert(test_pair(1, 'a'));

  test_node *node_4th_0e = tree.root();
  test_node *node_header = tree.header();
  test_node *node_nil = tree.nil();

  ASSERT_EQ(next(node_4th_0e, node_nil), node_header);
}

TEST_F(TreeTestF, PrevTest) {
  ASSERT_EQ(prev(node_2nd_m3i, node_nil)->item.second,
            node_1st_m5f->item.second);
  ASSERT_EQ(prev(node_3rd_m1c, node_nil)->item.second,
            node_2nd_m3i->item.second);
  ASSERT_EQ(prev(node_4th_0e, node_nil)->item.second,
            node_3rd_m1c->item.second);
  ASSERT_EQ(prev(node_5th_1a, node_nil)->item.second, node_4th_0e->item.second);
  ASSERT_EQ(prev(node_6th_10d, node_nil)->item.second,
            node_5th_1a->item.second);
  ASSERT_EQ(prev(node_last_20h, node_nil)->item.second,
            node_8th_19g->item.second);
  ASSERT_EQ(prev(node_header, node_nil)->item.second,
            node_last_20h->item.second);
  // beginのprev
  ASSERT_EQ(prev(node_1st_m5f, node_nil)->item.second,
            node_header->item.second);
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
  tree.insert(test_pair(1, 'a'));

  test_node *node_4th_0e = tree.root();
  test_node *node_header = tree.header();
  test_node *node_nil = tree.nil();

  ASSERT_EQ(prev(node_4th_0e, node_nil), node_header);
}

TEST_F(TreeTestF, BeginTest) {
  test_itr it = tree.begin();
  test_const_itr c_it = tree.begin();
  ASSERT_EQ(*it, node_1st_m5f->item);
  ASSERT_EQ(*c_it, node_1st_m5f->item);
  // *c_it = node_1st_m5f->item;
}

TEST_F(TreeTestF, RBeginTest) {
  test_rev_itr it = tree.rbegin();
  test_const_rev_itr c_it = tree.rbegin();
  ASSERT_EQ(*it, node_last_20h->item);
  ASSERT_EQ(*c_it, node_last_20h->item);
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
  ASSERT_EQ(*it, node_1st_m5f->item);
  ASSERT_EQ(*c_it, node_1st_m5f->item);
}

TEST_F(TreeTestF, IteratorArrowOperatorTest) {
  test_itr it = tree.begin();
  ASSERT_EQ(it->first, node_1st_m5f->item.first);
}

TEST_F(TreeTestF, IteratorIncrementTest) {
  test_itr it = tree.begin();
  ++it;
  ASSERT_EQ(*it, node_2nd_m3i->item);
  it++;
  ASSERT_EQ(*it, node_3rd_m1c->item);

  test_itr def_it;
  ++it;
  it++;
  *it;
}

TEST_F(TreeTestF, IteratorDecrementTest) {
  test_itr it = tree.end();
  --it;
  ASSERT_EQ(*it, node_last_20h->item);
  it--;
  ASSERT_EQ(*it, node_8th_19g->item);

  test_itr def_it;
  --it;
  it--;
  *it;
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
  empty_tree.insert(test_pair(1, 'a'));
  ASSERT_FALSE(empty_tree.empty());
  ASSERT_FALSE(tree.empty());
}

TEST_F(TreeTestF, SizeTest) {
  test_tree empty_tree;

  ASSERT_EQ(empty_tree.size(), 0);
  empty_tree.insert(test_pair(1, 'a'));
  ASSERT_EQ(empty_tree.size(), 1);
  ASSERT_EQ(tree.size(), default_size);
  // erase実装後テスト追加すること
}

TEST_F(TreeTestF, Insert1FailTest) {
  test_pair dup_key_pair(1, 'z');
  ft::pair< test_itr, bool > failed = tree.insert(dup_key_pair);
  ASSERT_FALSE(failed.second);
  ASSERT_EQ(failed, ft::make_pair(test_itr(node_5th_1a, node_nil), false));
}

TEST_F(TreeTestF, Insert1SuccessTest) {
  test_pair original_key_pair(42, 'z');
  ft::pair< test_itr, bool > success = tree.insert(original_key_pair);
  ASSERT_TRUE(success.second);
  test_itr inserted = success.first;
  ASSERT_EQ(inserted->first, 42);
  ASSERT_EQ(inserted->second, 'z');
  inserted--;
  ASSERT_EQ(inserted, test_itr(node_last_20h, node_nil));
}

TEST_F(TreeTestF, InsertHintFailTest) {
  test_pair dup_key_pair(1, 'z');
  test_itr it = tree.begin();
  test_itr disrupted = tree.insert(it, dup_key_pair);
  ASSERT_EQ(disrupted->first, 1);
  ASSERT_EQ(disrupted->second, 'a');
  disrupted--;
  ASSERT_EQ(disrupted, test_itr(node_4th_0e, node_nil));
}

TEST_F(TreeTestF, InsertHintSuccessTest) {
  test_pair original_key_pair(42, 'z');
  test_itr it = tree.begin();
  test_itr inserted = tree.insert(it, original_key_pair);
  ASSERT_EQ(inserted->first, 42);
  ASSERT_EQ(inserted->second, 'z');
  inserted--;
  ASSERT_EQ(inserted, test_itr(node_last_20h, node_nil));
}

TEST_F(TreeTestF, InsertRangeTest) {
  std::vector< test_pair > v;
  for (int i = 100; i < 110; i++) {
    v.push_back(test_pair(i, 'x'));
  }
  tree.insert(v.begin(), v.end());
  ASSERT_EQ(tree.size(), default_size + 10);
  for (int i = 100; i < 110; i++) {
    ASSERT_EQ(tree.find(i)->second, 'x');
  }
}

TEST_F(TreeTestF, Erase1Test) {
  tree.erase(test_itr(node_3rd_m1c, node_nil));
  ASSERT_EQ(tree.find(-1), tree.end());
  ASSERT_EQ(tree.size(), default_size - 1);
}

TEST_F(TreeTestF, EraseKeySuccessTest) {
  test_tree::size_type ret = tree.erase(node_3rd_m1c->item.first);
  ASSERT_EQ(ret, 1);
  ASSERT_EQ(tree.find(-1), tree.end());
  ASSERT_EQ(tree.size(), default_size - 1);
}

TEST_F(TreeTestF, EraseKeyFailTest) {
  test_tree::size_type ret = tree.erase(42);
  ASSERT_EQ(ret, 0);
  ASSERT_EQ(tree.size(), default_size);
}

TEST_F(TreeTestF, EraseRangeTwoElementTest) {
  test_itr itr_3rd(node_3rd_m1c, node_nil);  // 0
  test_itr itr_5th(node_5th_1a, node_nil);   // 10
  tree.erase(itr_3rd, itr_5th);
  ASSERT_EQ(tree.size(), default_size - 2);
  tree.print();
}

TEST_F(TreeTestF, EraseRangeALLTest) {
  tree.erase(tree.begin(), tree.end());
  ASSERT_EQ(tree.size(), 0);
  tree.erase(tree.begin(), tree.end());
}

TEST_F(TreeTestF, ClearTest) {
  tree.clear();
  ASSERT_EQ(tree.size(), 0);
  tree.clear();
  ASSERT_EQ(tree.size(), 0);
}

TEST(TreeTest, ClearEmptyMapTest) {
  test_tree empty;
  empty.clear();
  ASSERT_EQ(empty.size(), 0);
  empty.clear();
  ASSERT_EQ(empty.size(), 0);
}

TEST_F(TreeTestF, CountTest) {
  ASSERT_EQ(tree.count(10), 1);
  ASSERT_EQ(tree.count(11), 0);
  tree.erase(10);
  ASSERT_EQ(tree.count(10), 0);
}

TEST_F(TreeTestF, FindTest) {
  ASSERT_EQ(tree.find(10), test_itr(node_6th_10d, node_nil));
  ASSERT_EQ(tree.find(10)->first, 10);
  ASSERT_EQ(tree.find(11), tree.end());
  tree.erase(10);
  ASSERT_EQ(tree.find(10), tree.end());
}

TEST_F(TreeTestF, ConstFindTest) {
  const test_tree const_tree(tree);
  ASSERT_EQ(const_tree.find(10)->first, 10);
  ASSERT_EQ(const_tree.find(11), const_tree.end());
}

TEST_F(TreeTestF, LowerBoundTest) {
  ASSERT_EQ(tree.lower_bound(10), test_itr(node_6th_10d, node_nil));
  ASSERT_EQ(tree.lower_bound(9), test_itr(node_6th_10d, node_nil));
  ASSERT_EQ(tree.lower_bound(100), tree.end());
}

TEST_F(TreeTestF, ConstLowerBoundTest) {
  const test_tree const_tree(tree);
  ASSERT_EQ(const_tree.lower_bound(10)->first, 10);
  ASSERT_EQ(const_tree.lower_bound(9)->first, 10);
  ASSERT_EQ(const_tree.lower_bound(100), const_tree.end());
}

TEST_F(TreeTestF, UpperBoundTest) {
  ASSERT_EQ(tree.upper_bound(10), test_itr(node_7th_15b, node_nil));
  ASSERT_EQ(tree.upper_bound(9), test_itr(node_6th_10d, node_nil));
  ASSERT_EQ(tree.upper_bound(100), tree.end());
}

TEST_F(TreeTestF, ConstUpperBoundTest) {
  const test_tree const_tree(tree);
  ASSERT_EQ(const_tree.upper_bound(10)->first, 15);
  ASSERT_EQ(const_tree.upper_bound(9)->first, 10);
  ASSERT_EQ(const_tree.upper_bound(100), const_tree.end());
}

TEST_F(TreeTestF, EqualRangeTest) {
  ASSERT_EQ(tree.equal_range(10).first, test_itr(node_6th_10d, node_nil));
  ASSERT_EQ(tree.equal_range(10).second, test_itr(node_7th_15b, node_nil));
  ASSERT_EQ(tree.equal_range(9).first, test_itr(node_6th_10d, node_nil));
  ASSERT_EQ(tree.equal_range(9).second, test_itr(node_6th_10d, node_nil));
  ASSERT_EQ(tree.equal_range(15).first, test_itr(node_7th_15b, node_nil));
  ASSERT_EQ(tree.equal_range(15).second, test_itr(node_8th_19g, node_nil));
  ASSERT_EQ(tree.equal_range(100).first, tree.end());
  ASSERT_EQ(tree.equal_range(100).second, tree.end());
}

TEST_F(TreeTestF, CompareOperatorTest) {
  test_tree copy(tree);
  test_tree appended(tree);
  appended.insert(test_pair(8, 'b'));
  // appended.print_with_itr();
  ASSERT_EQ(appended.size(), default_size + 1);

  ASSERT_TRUE(tree == copy);
  ASSERT_FALSE(tree != copy);
  ASSERT_FALSE(tree > copy);
  ASSERT_TRUE(tree >= copy);
  ASSERT_FALSE(tree < copy);
  ASSERT_TRUE(tree <= copy);

  ASSERT_FALSE(tree == appended);
  ASSERT_TRUE(tree != appended);
  ASSERT_TRUE(tree > appended);
  ASSERT_TRUE(tree >= appended);
  ASSERT_FALSE(tree < appended);
  ASSERT_FALSE(tree <= appended);
}

// rightに子なし
TEST_F(TreeTestF, RotateLeftNoChildTest) {
  test_tree copy(tree);

  tree.print();
  tree.rotate_left(node_2nd_m3i);
  tree.print();
  ASSERT_TRUE(tree == copy);
}

// rightに子あり
TEST_F(TreeTestF, RotateLeftChildTest) {
  test_tree copy(tree);

  tree.print();
  tree.rotate_left(node_7th_15b);
  tree.print();
  ASSERT_TRUE(tree == copy);
}

// rightが存在しない
TEST_F(TreeTestF, RotateLeftNoRightTest) {
  test_tree copy(tree);

  tree.print();
  tree.rotate_left(node_last_20h);
  tree.print();
  ASSERT_TRUE(tree == copy);
}

// root
TEST_F(TreeTestF, RotateLeftRootTest) {
  test_tree copy(tree);

  tree.print();
  tree.rotate_left(node_5th_1a);
  tree.print();
  ASSERT_TRUE(tree == copy);
}

// leftに子なし
TEST_F(TreeTestF, RotateRightNoChildTest) {
  test_tree copy(tree);

  tree.print();
  tree.rotate_right(node_7th_15b);
  tree.print();
  ASSERT_TRUE(tree == copy);
}

// leftに子あり
TEST_F(TreeTestF, RotateRightChildTest) {
  test_tree copy(tree);

  tree.print();
  tree.rotate_right(node_3rd_m1c);
  tree.print();
  ASSERT_TRUE(tree == copy);
}

// root
TEST_F(TreeTestF, RotateRightRootTest) {
  test_tree copy(tree);

  tree.print();
  tree.rotate_right(node_5th_1a);
  tree.print();
  ASSERT_TRUE(tree == copy);
}

TEST_F(TreeTestF, NilTest) {
  ASSERT_NE(node_nil->color, ft::red);
  ASSERT_EQ(node_nil->color, ft::black);
}

TEST_F(TreeTestF, SwapColorsTest) {
  ASSERT_EQ(node_1st_m5f->color, ft::red);
  ASSERT_EQ(node_nil->color, ft::black);
  tree.swap_colors(node_1st_m5f, node_nil);
  ASSERT_EQ(node_1st_m5f->color, ft::black);
  ASSERT_EQ(node_nil->color, ft::red);
}

TEST(RBTreeTest, OnenodeTest) {
  test_tree rb_tree;
  rb_tree.insert(test_pair(1, 'a'));
  rb_tree.verify();
}

TEST(RBTreeTest, TwoNodeTest) {
  test_tree rb_tree;
  rb_tree.insert(test_pair(1, 'a'));
  rb_tree.insert(test_pair(15, 'b'));
  rb_tree.verify();
}

TEST(RBTreeTest, FourNodeTest) {
  test_tree rb_tree;
  rb_tree.insert(test_pair(1, 'a'));
  rb_tree.insert(test_pair(15, 'b'));
  rb_tree.insert(test_pair(-1, 'c'));
  rb_tree.insert(test_pair(10, 'd'));
  rb_tree.verify();
}

TEST(RBTreeTest, FiveNodeTest) {
  test_tree rb_tree;
  rb_tree.insert(test_pair(1, 'a'));
  rb_tree.insert(test_pair(15, 'b'));
  rb_tree.insert(test_pair(-1, 'c'));
  rb_tree.insert(test_pair(10, 'd'));
  rb_tree.insert(test_pair(0, 'e'));
  rb_tree.verify();
}

TEST(RBTreeTest, SixNodeTest) {
  test_tree rb_tree;
  rb_tree.insert(test_pair(1, 'a'));
  rb_tree.insert(test_pair(15, 'b'));
  rb_tree.insert(test_pair(-1, 'c'));
  rb_tree.insert(test_pair(10, 'd'));
  rb_tree.insert(test_pair(0, 'e'));
  rb_tree.insert(test_pair(-5, 'f'));
  rb_tree.verify();
}

TEST(RBTreeTest, SevenNodeTest) {
  test_tree rb_tree;
  rb_tree.insert(test_pair(1, 'a'));
  rb_tree.insert(test_pair(15, 'b'));
  rb_tree.insert(test_pair(-1, 'c'));
  rb_tree.insert(test_pair(10, 'd'));
  rb_tree.insert(test_pair(0, 'e'));
  rb_tree.insert(test_pair(-5, 'f'));
  rb_tree.insert(test_pair(20, 'g'));
  rb_tree.verify();
}

TEST_F(TreeTestF, VerifyTest) {
  ;
  tree.verify();
}

// rb_tree.insert(test_pair(19, 'h'));
// rb_tree.insert(test_pair(-3, 'i'));
