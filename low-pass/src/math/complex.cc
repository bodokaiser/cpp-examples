#include "math/math.h"

namespace math {

std::vector<int16_t>
to_real(std::vector<std::complex<double>> complex) {
    std::vector<int16_t> real(complex.size());
    std::transform(complex.begin(), complex.end(), real.begin(),
        [](std::complex<double> x) { return static_cast<int16_t>(x.real()); });

    return real;
}

}
