#include "math.hpp"

#include <iostream>

int main() {
  math::Vector<double, 3> x;
  math::Vector<double, 3> y{1, 2, 3};

  std::cout << "x: " << x << std::endl;
  std::cout << "y: " << y << std::endl;
}
