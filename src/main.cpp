#include "xvector/xvector.hpp"
#include <algorithm>
#include <iostream>

int main() {
  Xvector<int> v{4, 2, 3};

  for (auto &val : v) {
    val++;
  }

  for (auto &val : v) {
    std::cout << val << " ";
  }

  std::cout << "\n";

  std::sort(v.begin(), v.end());

  for (auto &val : v) {
    std::cout << val << " ";
  }
  try {
    v.at(100);
  } catch (const std::out_of_range &e) {
    std::cout << e.what() << "\n";
  }

  return 0;
}
