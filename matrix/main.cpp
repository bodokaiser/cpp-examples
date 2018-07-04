#include <iostream>

#include "matrix.hpp"

int main() {
  Matrix<double> A(2, 2);
  A(0, 1) = 1.0;
  A(1, 0) = -1.0;
  std::cout << A << std::endl;
  std::cout << A(1, 0) << std::endl;

  const Matrix<double> B(A);
  std::cout << B << std::endl;
  std::cout << B(1, 0) << std::endl;

  Matrix<double> C;
  C = B;
  std::cout << C << std::endl;
  C(1, 1) = 2;
  std::cout << C << std::endl;
}
