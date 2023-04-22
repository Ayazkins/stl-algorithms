#include "../lib/algorithms.h"
#include <gtest/gtest.h>
#include <vector>
#include <list>

TEST(AlgorithmsTest, all_of) {
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  auto p = [](const int x) {return x > 0;};
  EXPECT_TRUE(my_all_of(v.begin(), v.end(), p));
  v.push_back(-10);
  EXPECT_FALSE(my_all_of(v.begin(), v.end(), p));
}

TEST(AlgorithmsTest, any_of) {
  std::vector<int> v{-1, -2, -3, -4, -5, -6};
  auto p = [](const int x) {return x > 0;};
  EXPECT_FALSE(my_any_of(v.begin(), v.end(), p));
  v.push_back(10);
  EXPECT_TRUE(my_any_of(v.begin(), v.end(), p));
}

TEST(AlgorithmsTest, none_of) {
  std::vector<int> v{-1, -2, -3, -4, -5, -6};
  auto p = [](const int x) {return x > 0;};
  EXPECT_TRUE(my_none_of(v.begin(), v.end(), p));
  v.push_back(10);
  EXPECT_FALSE(my_none_of(v.begin(), v.end(), p));
}

TEST(AlgorithmsTest, one_of) {
  std::vector<int> v{1, -2, -3, -4, -5, -6};
  auto p = [](const int x) {return x > 0;};
  EXPECT_TRUE(my_one_of(v.begin(), v.end(), p));
  v[0] = -1;
  EXPECT_FALSE(my_one_of(v.begin(), v.end(), p));
  v[0] = 1;
  v[1] = 2;
  EXPECT_FALSE(my_one_of(v.begin(), v.end(), p));
}

TEST(AlgorithmsTest, is_sorted) {
  std::vector<int> v{-1, -2, -3, -4, -5, -6};
  auto p = [](const int x, const int y) {return y < x;};
  EXPECT_TRUE(my_is_sorted(v.begin(), v.end(), p));
  v.push_back(10);
  EXPECT_FALSE(my_is_sorted(v.begin(), v.end(), p));
}

TEST(AlgorithmsTest, is_partioned) {
  std::vector<int> v{-1, -2, -3, 4, 5, 6};
  auto p = [](const int x) {return x > 0;};
  EXPECT_TRUE(my_is_partitioned(v.begin(), v.end(), p));
  v.push_back(-10);
  EXPECT_FALSE(my_is_partitioned(v.begin(), v.end(), p));
}

TEST(AlgorithmsTest, find_not) {
  std::vector<int> v (10, 0);
  v.push_back(239);
  v[0] = 239;
  EXPECT_TRUE((*my_find_not(v.begin(), v.end(), 0)) == 239);
  EXPECT_TRUE(my_find_not(v.begin(), v.end(), 0) == v.begin());
}

TEST(AlgorithmsTest, find_backward) {
  std::vector<int> v (10, 0);
  v.push_back(239);
  v[0] = 239;
  EXPECT_TRUE((*my_find_backward(v.begin(), v.end(), 239)) == 239);
  EXPECT_TRUE(my_find_backward(v.begin(), v.end(), 239) == v.end() - 1);
}

TEST(AlgorithmsTest, is_palindrome) {
  std::vector<int> v{-1, -2, 3, 4, -5, -6};
  auto p = [](const int x) {return x > 0;};
  EXPECT_TRUE(my_is_palindrome(v.begin(), v.end(), p));
  v.push_back(10);
  EXPECT_FALSE(my_is_palindrome(v.begin(), v.end(), p));
}

TEST(AlgorithmsTest, xrange) {
  auto x = xrange(1.5, 5.5);
  std::vector<double> v{x.begin(), x.end()};
  auto a = 1.5;
  for (auto val : v) {
	EXPECT_EQ(val, a);
	a += 1;
  }
  int b = 1;
  for(auto val : xrange(1, 6, 2)) {
	EXPECT_EQ(val, b);
	b += 2;
  }
  auto c = xrange(4);
  b = 0;
  std::vector<int> d{c.begin(), c.end()};
  for (auto val : d) {
	EXPECT_EQ(val , b);
	b++;
  }
}

TEST(AlgorithmsTest, zip) {
  std::vector<int> v{-1, -2, 3, 4, -5, -6};
  std::list<char> v2{'a', 'b', 'c', 'd'};
  auto x = zip(v, v2);
  int index = 0;
  for (auto val : x) {
	EXPECT_EQ(val.first, v[index]);
	EXPECT_EQ(val.second, (*v2.begin() + index));
	index++;
  }
}





