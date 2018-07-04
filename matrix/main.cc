#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T> size_t num_digits(T number) {
  if (number < 0)
    number *= -1;

  return std::ceil(std::log10(number));
}

template <typename T> class Matrix {
public:
  Matrix() : rows_(0), cols_(0), data_(0) {}
  Matrix(size_t m, size_t n) : rows_(m), cols_(n), data_(m * n) {}

  T &operator()(size_t i, size_t j) {
    if (i >= rows_ || j >= cols_)
      throw std::out_of_range("index out of range");

    return data_[i * rows_ + j];
  }

  T operator()(size_t i, size_t j) const {
    if (i >= rows_ || j >= cols_)
      throw std::out_of_range("index out of range");

    return data_[i * rows_ + j];
  }

  friend std::ostream &operator<<(std::ostream &stream,
                                  const Matrix<T> &matrix) {
    T max = *std::max_element(matrix.data_.begin(), matrix.data_.end());
    T min = *std::min_element(matrix.data_.begin(), matrix.data_.end());

    size_t width = 3 + std::max(num_digits(min), num_digits(max));

    for (size_t i = 0; i < matrix.cols_; i++) {
      for (size_t j = 0; j < matrix.rows_; j++) {
        T element = matrix.data_[i * matrix.rows_ + j];

        stream << std::left << std::setw(width) << std::setfill(' ') << element;
      }
      stream << std::endl;
    }

    return stream;
  }

private:
  size_t rows_;
  size_t cols_;
  std::vector<T> data_;
};

int main(int argc, char **argv) {
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
