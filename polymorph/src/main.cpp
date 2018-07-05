#include <iostream>

#include "math.hpp"

int main() {
  math::Variable x("x");
  math::Constant c(1);

  // math::Expression expr = c + x + x;

  std::cout << x.str() << std::endl;
  std::cout << c.str() << std::endl;
}
