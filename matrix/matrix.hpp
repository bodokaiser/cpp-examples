#pragma once

#include <cmath>
#include <iomanip>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <utility>

using dim_t = std::pair<size_t, size_t>;

template <typename T>
class Matrix {
 public:
  Matrix() : Matrix(0, 0){};
  Matrix(const Matrix& matrix) : Matrix(matrix.rows(), matrix.cols()) {
    std::copy(matrix.data_.get(), matrix.data_.get() + size(), data_.get());
  }
  Matrix(Matrix&& matrix) noexcept
      : dim_(matrix.dim_), data_(std::move(matrix.data_)) {
    matrix.dim_ = dim_t(0, 0);
    matrix.data_ = nullptr;
  }
  Matrix(size_t m, size_t n) noexcept : dim_(m, n) {
    data_ = std::make_unique<T[]>(m * n);

    fill(0);
  }
  ~Matrix() = default;

  dim_t dim() const { return dim_; };
  size_t size() const { return rows() * cols(); }
  size_t rows() const { return dim().first; }
  size_t cols() const { return dim().second; }

  void fill(T value) {
    for (size_t i = 0; i < cols(); i++) {
      for (size_t j = 0; j < rows(); j++) {
        data_[i * rows() + j] = value;
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
    data_ = std::move(matrix.data_);
    dim_ = matrix.dim_;
    matrix.dim_ = dim_t(0, 0);

    return *this;
  }

  T& at(size_t i, size_t j) {
    if (i >= rows() || j >= cols()) {
      throw std::out_of_range("index out of range");
    }

    return data_[i * rows() + j];
  }

  T at(size_t i, size_t j) const {
    if (i >= rows() || j >= cols()) {
      throw std::out_of_range("index out of range");
    }

    return data_[i * rows() + j];
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.cols(); i++) {
      for (size_t j = 0; j < matrix.rows(); j++) {
        T element = matrix.data_[i * matrix.rows() + j];

        stream << std::left << std::setw(4) << std::setfill(' ') << element;
      }

      if (i != matrix.cols() - 1) {
        stream << std::endl;
      }
    }

    return stream;
  }

 private:
  dim_t dim_;
  std::unique_ptr<T[]> data_;
};
