#include <gtest/gtest.h>

#include "../../includes/rb_tree.hpp"

typedef ft::pair< int, char > pair_t;
typedef ft::rb_tree_node< pair_t > node_t;
typedef ft::rb_tree< int, pair_t, std::less< int > > tree_t;
typedef tree_t::iterator iter_t;
typedef tree_t::const_iterator citer_t;
typedef tree_t::reverse_iterator rev_iter_t;
typedef tree_t::const_reverse_iterator crev_iter_t;

class RBTreeEraseTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    tree.insert(pair_t(1, 'a'));
    tree.insert(pair_t(15, 'b'));
    tree.insert(pair_t(-1, 'c'));
    tree.insert(pair_t(10, 'd'));
    tree.insert(pair_t(0, 'e'));
    tree.insert(pair_t(-5, 'f'));
    tree.insert(pair_t(20, 'g'));
    tree.insert(pair_t(19, 'h'));
    tree.insert(pair_t(-3, 'i'));
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
  tree_t tree;
  node_t *node_nil;
  node_t *node_1st_m5f;
  node_t *node_2nd_m3i;
  node_t *node_3rd_m1c;
  node_t *node_4th_0e;
  node_t *node_5th_1a;
  node_t *node_6th_10d;
  node_t *node_7th_15b;
  node_t *node_8th_19g;
  node_t *node_last_20h;
  node_t *node_header;
  tree_t::size_type default_size;
};

TEST_F(RBTreeEraseTest, Print) {
  tree.print();
  ;
}

TEST_F(RBTreeEraseTest, Erase1Test) {
  tree.erase(iter_t(node_3rd_m1c, node_nil));
  ASSERT_EQ(tree.find(-1), tree.end());
  ASSERT_EQ(tree.size(), default_size - 1);
  tree.verify();
}

TEST_F(RBTreeEraseTest, EraseKeySuccessTest) {
  tree_t::size_type ret = tree.erase(node_3rd_m1c->item.first);
  ASSERT_EQ(ret, 1);
  ASSERT_EQ(tree.find(-1), tree.end());
  ASSERT_EQ(tree.size(), default_size - 1);
  tree.verify();
}

TEST_F(RBTreeEraseTest, EraseKeyFailTest) {
  tree_t::size_type ret = tree.erase(42);
  ASSERT_EQ(ret, 0);
  ASSERT_EQ(tree.size(), default_size);
}

TEST_F(RBTreeEraseTest, EraseNode2Test) {
  tree.erase(tree.find(-3));
  ASSERT_EQ(tree.find(-3), tree.end());
  ASSERT_EQ(tree.size(), default_size - 1);
  tree.verify();
}

TEST_F(RBTreeEraseTest, EraseNode3Test) {
  tree.erase(tree.find(0));
  ASSERT_EQ(tree.find(0), tree.end());
  ASSERT_EQ(tree.size(), default_size - 1);
  tree.verify();
}

TEST_F(RBTreeEraseTest, EraseRootTest) {
  tree.erase(tree.find(1));
  ASSERT_EQ(tree.find(1), tree.end());
  ASSERT_EQ(tree.size(), default_size - 1);
  tree.verify();
}

TEST_F(RBTreeEraseTest, Erase2NodeTest) {
  tree.erase(iter_t(node_3rd_m1c, node_nil));
  ASSERT_EQ(tree.find(-1), tree.end());
  tree.verify();
  tree.erase(tree.find(0));
  ASSERT_EQ(tree.find(0), tree.end());
  ASSERT_EQ(tree.size(), default_size - 2);
  tree.verify();
}

TEST_F(RBTreeEraseTest, EraseRangeTwoElementTest) {
  iter_t itr_3rd(node_3rd_m1c, node_nil);  // 0
  iter_t itr_5th(node_5th_1a, node_nil);   // 10
  tree.erase(itr_3rd, itr_5th);
  ASSERT_EQ(tree.find(-1), tree.end());
  ASSERT_EQ(tree.find(0), tree.end());
  ASSERT_EQ(tree.size(), default_size - 2);
  tree.verify();
}

TEST_F(RBTreeEraseTest, EraseRange12Test) {
  iter_t itr_1st(node_1st_m5f, node_nil);  // 0
  iter_t itr_3rd(node_3rd_m1c, node_nil);  // 10
  tree.erase(itr_1st, itr_3rd);
  ASSERT_EQ(tree.find(-5), tree.end());
  ASSERT_EQ(tree.find(-3), tree.end());
  ASSERT_EQ(tree.size(), default_size - 2);
  tree.verify();
}

TEST_F(RBTreeEraseTest, EraseRangeALLTest) {
  tree.erase(tree.begin(), tree.end());
  ASSERT_EQ(tree.size(), 0);
  tree.erase(tree.begin(), tree.end());
  ASSERT_EQ(tree.size(), 0);
  tree.verify();
}

TEST_F(RBTreeEraseTest, ClearTest) {
  tree.clear();
  ASSERT_EQ(tree.size(), 0);
  tree.clear();
  ASSERT_EQ(tree.size(), 0);
  tree.verify();
}

TEST(TreeTest, ClearEmptyMapTest) {
  tree_t empty;
  empty.clear();
  ASSERT_EQ(empty.size(), 0);
  empty.clear();
  ASSERT_EQ(empty.size(), 0);
}

#ifndef COUNT
#define COUNT 1000
#endif

class RBTreeRandomEraseTest : public ::testing::Test {
  typedef std::vector< pair_t > test_vec;

 protected:
  virtual void SetUp() {
    for (int i = 0; i < COUNT; i++) {
      src_vec.push_back(ft::make_pair(i, ('a' + i) % 90 + 33));
      std::random_shuffle(src_vec.begin(), src_vec.end());
    }
    for (test_vec::iterator it = src_vec.begin(); it != src_vec.end(); it++) {
      tree.insert(*it);
    }
  }
  virtual void TearDown() {}

  test_vec src_vec;
  tree_t tree;
};

TEST_F(RBTreeRandomEraseTest, EraseManyTest) {
  ASSERT_EQ(src_vec.size(), COUNT);
  ASSERT_EQ(tree.size(), COUNT);
  tree.erase(tree.begin(), tree.end());
  ASSERT_EQ(tree.size(), 0);
}

TEST_F(RBTreeRandomEraseTest, VerifyTest) {
  tree.verify();
  ;
}

TEST_F(RBTreeRandomEraseTest, RandomEraseTest) {
  srand(time(NULL));
  for (int i = 0; i < COUNT / 4; i++) {
    size_t rand_index = rand() % src_vec.size();
    pair_t::first_type key = src_vec[rand_index].first;
    tree.erase(key);
    tree.verify();
  }
}
