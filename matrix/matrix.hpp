#pragma once

#include <cmath>
#include <iomanip>
#include <memory>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace linalg {

using dim_t = std::pair<size_t, size_t>;

enum class Allocator { vector, raw_pointer, unique_pointer };

template <typename T>
class MatrixBase {
 public:
  MatrixBase() : MatrixBase(0, 0){};
  MatrixBase(size_t m, size_t n) : dim_(m, n){};

  dim_t dim() const;
  size_t size() const;
  size_t cols() const;
  size_t rows() const;
  void fill(T value);

  virtual T& at(size_t i, size_t j) = 0;
  virtual T at(size_t i, size_t j) const = 0;

  friend std::ostream& operator<<(std::ostream& stream,
                                  const MatrixBase<T>& matrix) {
    for (size_t i = 0; i < matrix.cols(); i++) {
      for (size_t j = 0; j < matrix.rows(); j++) {
        stream << std::left << std::setw(4) << std::setfill(' ')
               << matrix.at(i, j);
      }

      if (i != matrix.cols() - 1) {
        stream << std::endl;
      }
    }

    return stream;
  }

 protected:
  dim_t dim_;

  void assert_indices(size_t i, size_t j) const;
};

template <typename T>
dim_t MatrixBase<T>::dim() const {
  return dim_;
}

template <typename T>
size_t MatrixBase<T>::size() const {
  return rows() * cols();
}

template <typename T>
size_t MatrixBase<T>::rows() const {
  return dim().first;
}

template <typename T>
size_t MatrixBase<T>::cols() const {
  return dim().second;
}

template <typename T>
void MatrixBase<T>::fill(T value) {
  for (size_t i = 0; i < cols(); i++) {
    for (size_t j = 0; j < rows(); j++) {
      at(i, j) = value;
    }
  }
}

template <typename T>
void MatrixBase<T>::assert_indices(size_t i, size_t j) const {
  if (i >= rows() || j >= cols()) {
    throw std::out_of_range("index out of range");
  }
}

template <Allocator A, typename T>
class Matrix : public MatrixBase<T> {};

template <typename T>
class Matrix<Allocator::vector, T> : public MatrixBase<T> {
 public:
  Matrix(size_t n, size_t m);

  T& at(size_t i, size_t j);
  T at(size_t i, size_t j) const;

 private:
  std::vector<T> data_;
};

template <typename T>
Matrix<Allocator::vector, T>::Matrix(size_t n, size_t m) : MatrixBase<T>(n, m) {
  data_.resize(this->size());
}

template <typename T>
T& Matrix<Allocator::vector, T>::at(size_t i, size_t j) {
  this->assert_indices(i, j);

  return data_[i * this->rows() + j];
}

template <typename T>
T Matrix<Allocator::vector, T>::at(size_t i, size_t j) const {
  this->assert_indices(i, j);

  return data_[i * this->rows() + j];
}

template <typename T>
class Matrix<Allocator::raw_pointer, T> : public MatrixBase<T> {
 public:
  Matrix() : Matrix(0, 0){};
  Matrix(const Matrix<Allocator::raw_pointer, T>& matrix);
  Matrix(Matrix<Allocator::raw_pointer, T>&& matrix) noexcept;
  Matrix(size_t m, size_t n) noexcept;
  ~Matrix() noexcept;

  T& at(size_t i, size_t j);
  T at(size_t i, size_t j) const;

  Matrix<Allocator::raw_pointer, T>& operator=(
      const Matrix<Allocator::raw_pointer, T>& matrix) {
    Matrix<Allocator::raw_pointer, T> tmp(matrix);

    *this = std::move(tmp);

    return *this;
  }

  Matrix<Allocator::raw_pointer, T>& operator=(
      Matrix<Allocator::raw_pointer, T>&& matrix) noexcept {
    if (this == &matrix) {
      return *this;
    }
    if (data_ != nullptr) {
      delete[] data_;
    }
    data_ = matrix.data_;
    this->dim_ = matrix.dim_;
    matrix.data_ = nullptr;
    matrix.dim_ = dim_t(0, 0);

    return *this;
  }

 private:
  T* data_;
};

template <typename T>
Matrix<Allocator::raw_pointer, T>::Matrix(
    const Matrix<Allocator::raw_pointer, T>& matrix)
    : Matrix(matrix.rows(), matrix.cols()) {
  std::copy(matrix.data_, matrix.data_ + this->size(), data_);
}

template <typename T>
Matrix<Allocator::raw_pointer, T>::Matrix(
    Matrix<Allocator::raw_pointer, T>&& matrix) noexcept
    : MatrixBase<T>(matrix.rows(), matrix.cols()),
      data_(std::move(matrix.data_)) {
  matrix.data_ = nullptr;
  matrix.dim_ = dim_t(0, 0);
}

template <typename T>
Matrix<Allocator::raw_pointer, T>::Matrix(size_t m, size_t n) noexcept
    : MatrixBase<T>(m, n), data_(new T[m * n]) {
  this->fill(0);
}

template <typename T>
Matrix<Allocator::raw_pointer, T>::~Matrix() noexcept {
  delete[] data_;
}

template <typename T>
T& Matrix<Allocator::raw_pointer, T>::at(size_t i, size_t j) {
  this->assert_indices(i, j);

  return data_[i * this->rows() + j];
}

template <typename T>
T Matrix<Allocator::raw_pointer, T>::at(size_t i, size_t j) const {
  this->assert_indices(i, j);

  return data_[i * this->rows() + j];
}

template <typename T>
class Matrix<Allocator::unique_pointer, T> : public MatrixBase<T> {
 public:
  Matrix() : Matrix(0, 0){};
  Matrix(const Matrix<Allocator::unique_pointer, T>& matrix);
  Matrix(Matrix<Allocator::unique_pointer, T>&& matrix) noexcept;
  Matrix(size_t m, size_t n) noexcept;
  ~Matrix() = default;

  T& at(size_t i, size_t j);
  T at(size_t i, size_t j) const;

  Matrix<Allocator::unique_pointer, T>& operator=(
      const Matrix<Allocator::unique_pointer, T>& matrix) {
    Matrix<Allocator::unique_pointer, T> tmp(matrix);

    *this = std::move(tmp);

    return *this;
  }

  Matrix<Allocator::unique_pointer, T>& operator=(
      Matrix<Allocator::unique_pointer, T>&& matrix) noexcept {
    if (this == &matrix) {
      return *this;
    }
    data_ = std::move(matrix.data_);
    this->dim_ = matrix.dim_;
    matrix.dim_ = dim_t(0, 0);

    return *this;
  }

 private:
  std::unique_ptr<T[]> data_;
};

template <typename T>
Matrix<Allocator::unique_pointer, T>::Matrix(
    const Matrix<Allocator::unique_pointer, T>& matrix)
    : Matrix(matrix.rows(), matrix.cols()) {
  std::copy(matrix.data_.get(), matrix.data_.get() + this->size(), data_.get());
}

template <typename T>
Matrix<Allocator::unique_pointer, T>::Matrix(
    Matrix<Allocator::unique_pointer, T>&& matrix) noexcept
    : data_(std::move(matrix.data_)) {
  this->dim_ = dim_t(matrix.rows(), matrix.cols());
  matrix.dim_ = dim_t(0, 0);
  matrix.data_ = nullptr;
}

template <typename T>
Matrix<Allocator::unique_pointer, T>::Matrix(size_t m, size_t n) noexcept
    : MatrixBase<T>(m, n) {
  data_ = std::make_unique<T[]>(this->size());

  this->fill(0);
}

template <typename T>
T& Matrix<Allocator::unique_pointer, T>::at(size_t i, size_t j) {
  this->assert_indices(i, j);

  return data_[i * this->rows() + j];
}

template <typename T>
T Matrix<Allocator::unique_pointer, T>::at(size_t i, size_t j) const {
  this->assert_indices(i, j);

  return data_[i * this->rows() + j];
}

}  // namespace linalg
