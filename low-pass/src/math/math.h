#ifndef LOW_PASS_SRC_MATH_MATH_H_
#define LOW_PASS_SRC_MATH_MATH_H_

#include <algorithm>
#include <complex>
#include <vector>

namespace math {

std::vector<std::complex<double>> fft(std::vector<std::complex<double>>);

std::vector<std::complex<double>> inverse_fft(
    std::vector<std::complex<double>>);

template <typename T>
std::vector<std::complex<double>> complex(std::vector<T> real) {
  std::vector<std::complex<double>> complex(real.size());
  std::transform(real.begin(), real.end(), complex.begin(),
      [](T x) { return std::complex<double>(x, 0); });

  return complex;
}

template <typename T>
std::vector<T> real(std::vector<std::complex<double>> complex) {
  std::vector<T> real(complex.size());
  std::transform(complex.begin(), complex.end(), real.begin(),
      [](std::complex<double> x) { return static_cast<T>(x.real()); });

  return real;
}

}

#endif  // LOW_PASS_SRC_MATH_MATH_H_
