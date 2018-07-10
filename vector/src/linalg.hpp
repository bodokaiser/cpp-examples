#pragma once

#include <algorithm>
#include <exception>
#include <initializer_list>
#include <memory>
#include <ostream>
#include <utility>

namespace linalg {

template <typename T, size_t N>
class Vector {
 public:
  explicit Vector() noexcept;
  Vector(std::initializer_list<T> values) noexcept;
  Vector(const Vector<T, N>& vector) noexcept;
  Vector(Vector<T, N>&& vector) noexcept;
  ~Vector() = default;

  bool ok() const;
  void fill();

  T operator[](size_t i) const;
  T& operator[](size_t i);

  Vector<T, N>& operator=(const Vector<T, N>& vector) noexcept;
  Vector<T, N>& operator=(Vector<T, N>&& vector) noexcept;

  T operator*=(const Vector<T, N>& vector) const;
  Vector<T, N>& operator*=(const T& scalar);
  Vector<T, N>& operator+=(const Vector<T, N>& vector);
  Vector<T, N>& operator-=(const Vector<T, N>& vector);

 private:
  bool ok_ = true;
  std::unique_ptr<T[]> data_;
};

template <typename T, size_t N>
Vector<T, N>::Vector() noexcept : data_(new T[N]) {
  fill();
}

template <typename T, size_t N>
Vector<T, N>::Vector(std::initializer_list<T> values) noexcept : Vector() {
  size_t n = std::min(N, values.size());

  std::copy(values.begin(), values.begin() + n, data_.get());
}

template <typename T, size_t N>
Vector<T, N>::Vector(const Vector<T, N>& vector) noexcept : Vector() {
  std::copy(vector.data_.get(), vector.data_.get() + N, data_.get());
}

template <typename T, size_t N>
Vector<T, N>::Vector(Vector<T, N>&& vector) noexcept
    : data_(std::move(vector.data_)) {
  vector.data_ = nullptr;
  vector.ok_ = false;
}

template <typename T, size_t N>
void Vector<T, N>::fill() {
  for (size_t i = 0; i < N; i++) {
    data_[i] = 0;
  }
}

template <typename T, size_t N>
bool Vector<T, N>::ok() const {
  return ok_;
}

template <typename T, size_t N>
T Vector<T, N>::operator[](size_t i) const {
  if (data_ == nullptr) {
    throw std::logic_error("no data");
  }

  return data_[i];
};

template <typename T, size_t N>
T& Vector<T, N>::operator[](size_t i) {
  if (data_ == nullptr) {
    throw std::logic_error("no data");
  }

  return data_[i];
};

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator=(const Vector<T, N>& vector) noexcept {
  if (this == &vector) {
    return *this;
  }
  *this = Vector<T, N>(vector);

  return *this;
}

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator=(Vector<T, N>&& vector) noexcept {
  if (this == &vector) {
    return *this;
  }
  data_ = std::move(vector.data_);

  return *this;
}

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& vector) {
  for (size_t i = 0; i < N; i++) {
    data_[i] += vector[i];
  }

  return *this;
}

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& vector) {
  for (size_t i = 0; i < N; i++) {
    data_[i] -= vector[i];
  }

  return *this;
}

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator*=(const T& scalar) {
  for (size_t i = 0; i < N; i++) {
    data_[i] *= scalar;
  }

  return *this;
}

template <typename T, size_t N>
T Vector<T, N>::operator*=(const Vector<T, N>& vector) const {
  double sum = 0.;

  for (size_t i = 0; i < N; i++) {
    sum += vector[i] * data_[i];
  }

  return sum;
}

template <typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N>& lvector,
                       const Vector<T, N> rvector) {
  return Vector<T, N>(lvector) += rvector;
}

template <typename T, size_t N>
Vector<T, N> operator-(const Vector<T, N>& lvector,
                       const Vector<T, N> rvector) {
  return Vector<T, N>(lvector) -= rvector;
}

template <typename T, size_t N>
T operator*(const Vector<T, N>& lvector, const Vector<T, N> rvector) {
  return Vector<T, N>(lvector) *= rvector;
}

template <typename T, size_t N>
Vector<T, N> operator*(const T scalar, const Vector<T, N> vector) {
  return Vector<T, N>(vector) *= scalar;
}

template <typename T, size_t N>
Vector<T, N> operator*(const Vector<T, N> vector, const T scalar) {
  return Vector<T, N>(vector) *= scalar;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& stream, const Vector<T, N>& vector) {
  if (!vector.ok()) {
    return stream;
  }

  for (size_t i = 0; i < N - 1; i++) {
    stream << vector[i] << ", ";
  }
  stream << vector[N - 1];

  return stream;
}

}  // namespace linalg
