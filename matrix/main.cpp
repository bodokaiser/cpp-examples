#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T>
size_t num_digits(T number) {
  if (number < 0) {
    number *= -1;
  }

  return std::ceil(std::log10(number));
}

template <typename T>
class Matrix {
 public:
  Matrix() : Matrix(0, 0){};
  Matrix(const Matrix& matrix) : Matrix(matrix.rows_, matrix.cols_) {
    std::copy(matrix.data_, matrix.data_ + size(), data_);
  }
  Matrix(Matrix&& matrix) noexcept : data_(std::move(matrix.data_)) {
    rows_ = matrix.rows_;
    cols_ = matrix.cols_;
    matrix.data_ = nullptr;
  }
  Matrix(size_t m, size_t n) noexcept
      : rows_(m), cols_(n), data_(new T[m * n]) {
    fill(0);
  }
  ~Matrix() noexcept { delete[] data_; }

  size_t size() const { return rows_ * cols_; }
  size_t rows() const { return rows_; }
  size_t cols() const { return cols_; }

  void fill(T value) {
    for (size_t i = 0; i < cols_; i++) {
      for (size_t j = 0; j < rows_; j++) {
        data_[i * rows_ + j] = value;
      }
    }
  }

  Matrix& operator=(const Matrix& matrix) {
    Matrix tmp(matrix);

    *this = std::move(tmp);

    return *this;
  }

  Matrix& operator=(Matrix&& matrix) noexcept {
    if (this == &matrix) {
      return *this;
    }
    delete[] data_;
    data_ = matrix.data_;
    rows_ = matrix.rows_;
    cols_ = matrix.cols_;
    matrix.data_ = nullptr;

    return *this;
  }

  T& operator()(size_t i, size_t j) {
    if (i >= rows_ || j >= cols_) {
      throw std::out_of_range("index out of range");
    }

    return data_[i * rows_ + j];
  }

  T operator()(size_t i, size_t j) const {
    if (i >= rows_ || j >= cols_) {
      throw std::out_of_range("index out of range");
    }

    return data_[i * rows_ + j];
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.cols_; i++) {
      for (size_t j = 0; j < matrix.rows_; j++) {
        T element = matrix.data_[i * matrix.rows_ + j];

        stream << std::left << std::setw(4) << std::setfill(' ') << element;
      }

      if (i != matrix.cols_ - 1) {
        stream << std::endl;
      }
    }

    return stream;
  }

 private:
  size_t rows_ = 0;
  size_t cols_ = 0;
  T* data_;
};

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
