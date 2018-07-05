#pragma once

#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace math {

template <typename T, size_t N>
class Vector {
 public:
  Vector();
  Vector(std::initializer_list<T> values);
  Vector(const Vector<T, N>& vector);
  Vector(Vector<T, N>&& vector) noexcept;
  ~Vector() = default;

  T operator[](size_t i) const {
    if (i > N) {
      throw std::out_of_range("index out of range");
    }

    return data_[i];
  }

  Vector<T, N>& operator=(const Vector<T, N>& vector) {
    Vector<T, N> temp(vector);

    *this = std::move(temp);

    return *this;
  }

  Vector<T, N>& operator=(Vector<T, N>&& vector) noexcept {
    if (this == &vector) {
      return *this;
    }
    data_ = std::move(vector.data_);

    return *this;
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const Vector<T, N>& vector) {
    for (size_t i = 0; i < N - 1; i++) {
      stream << vector[i] << ", ";
    }

    stream << vector[N - 1];

    return stream;
  }

 private:
  std::unique_ptr<T[]> data_;
};

template <typename T, size_t N>
Vector<T, N>::Vector() : data_(std::make_unique<T[]>(N)) {
  for (size_t i = 0; i < N; i++) {
    data_[i] = 0;
  }
}

template <typename T, size_t N>
Vector<T, N>::Vector(std::initializer_list<T> values)
    : data_(std::make_unique<T[]>(N)) {
  if (values.size() != N) {
    throw std::length_error("initializer values and vector length missmatch");
  }

  std::copy(values.begin(), values.end(), data_.get());
}

template <typename T, size_t N>
Vector<T, N>::Vector(const Vector<T, N>& vector) : Vector(N) {
  std::copy(vector.data_.get(), vector.data_.get() + N, data_.get());
}

template <typename T, size_t N>
Vector<T, N>::Vector(Vector<T, N>&& vector) noexcept
    : data_(std::move(vector.data_)) {
  vector.data_ = nullptr;
}

}  // namespace math
