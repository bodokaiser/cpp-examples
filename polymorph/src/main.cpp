#include <iostream>

#include "math.hpp"

int main() {
  math::Variable x("x");
  math::Constant c(1);

  std::cout << "enter expression: " << std::endl;
  std::string token;

  while (std::cin >> token) {
    switch (token.data()[0]) {
      case '+':
        break;
      case '-':
        break;
      case '*':
        break;
      case '/':
        break;
    }

    std::cout << "token: " << token << std::endl;
  }

  std::cout << x.str() << std::endl;
  std::cout << c.str() << std::endl;
}
