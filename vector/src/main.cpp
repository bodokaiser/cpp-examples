#include <iostream>

#include "linalg.hpp"

int main() {
  linalg::Vector<double, 10> v1;
  linalg::Vector<double, 3> v2{1, 2, 3};
  linalg::Vector<double, 3> v3(v2);
  linalg::Vector<double, 3> v4(std::move(v2));
  linalg::Vector<double, 3> v5;

  v1[3] = 3;
  v5 = v4;
  v3[2] = 10;
  v5 += v3;

  std::cout << "v1: " << v1 << std::endl;
  // std::cout << "v2: " << v2 << std::endl;
  std::cout << "v3: " << v3 << std::endl;
  std::cout << "v4: " << v4 << std::endl;
  std::cout << "v5: " << v5 << std::endl;
  std::cout << "2*v3: " << 2. * v3 << std::endl;
  std::cout << "v3*v4: " << v3 * v4 << std::endl;
}
