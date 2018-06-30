#include <fftw3.h>

#include "math/math.h"

namespace math {

std::vector<std::complex<double>>
fft(std::vector<std::complex<double>> in) {
  std::vector<std::complex<double>> out(in.size());

  fftw_plan plan = fftw_plan_dft_1d(in.size(),
      reinterpret_cast<fftw_complex*>(in.data()),
      reinterpret_cast<fftw_complex*>(out.data()),
      FFTW_FORWARD, FFTW_ESTIMATE);

  fftw_execute(plan);
  fftw_destroy_plan(plan);

  return out;
}

std::vector<std::complex<double>>
inverse_fft(std::vector<std::complex<double>> in) {
  std::vector<std::complex<double>> out(in.size());

  fftw_plan plan = fftw_plan_dft_1d(in.size(),
      reinterpret_cast<fftw_complex*>(in.data()),
      reinterpret_cast<fftw_complex*>(out.data()),
      FFTW_BACKWARD, FFTW_ESTIMATE);

  fftw_execute(plan);
  fftw_destroy_plan(plan);

  return out;
}

}
