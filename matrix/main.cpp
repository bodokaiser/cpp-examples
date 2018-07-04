#include <iostream>

#include "matrix.hpp"

int main() {
  Matrix<double> A(2, 2);
  A.at(0, 1) = 1.0;
  A.at(1, 0) = -1.0;
  std::cout << A << std::endl;
  std::cout << A.at(1, 0) << std::endl;

  const Matrix<double> B(A);
  std::cout << B << std::endl;
  std::cout << B.at(1, 0) << std::endl;

  Matrix<double> C;
  C = B;
  std::cout << C << std::endl;
  C.at(1, 1) = 2;
  std::cout << C << std::endl;
}
