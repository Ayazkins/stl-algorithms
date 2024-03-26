#include <vector>
#include <list>
#include <iostream>
#include "../lib/algorithms.h"

int main() {
  std::vector<char> a {'a', 'b', 'c', 'd'};
  std::list<int> b {1, 2, 3, 4, 5};
  auto x = zip(a, b);
  std::vector<std::pair<char, int>> v{x.begin(), x.end()};
  for (auto i : v) {
	std::cout << i.first << ' ' << i.second << '\n';
  }
}