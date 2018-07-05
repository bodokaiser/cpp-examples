#include <iostream>

#include "matrix.hpp"

int main() {
  linalg::Matrix<linalg::Allocator::raw_pointer, double> A(2, 2);
  A.at(0, 1) = 1.0;
  A.at(1, 0) = -1.0;
  std::cout << "A: " << std::endl;
  std::cout << A << std::endl;
  std::cout << "A[1,0]: " << A.at(1, 0) << std::endl;

  const linalg::Matrix<linalg::Allocator::raw_pointer, double> B(std::move(A));
  std::cout << "B: " << std::endl;
  std::cout << B << std::endl;
  std::cout << "B[1,0]: " << B.at(1, 0) << std::endl;

  linalg::Matrix<linalg::Allocator::raw_pointer, double> C;
  C = B;
  std::cout << "C: " << std::endl;
  std::cout << C << std::endl;
  C.at(1, 1) = 2;
  std::cout << "C: " << std::endl;
  std::cout << C << std::endl;
}
