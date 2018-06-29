#include <iostream>
#include <fstream>
#include <string>

#include "audio/audio.h"
#include "math/math.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "missing arguments" << std::endl;

        return 1;
    }
    std::string input_path(argv[1]);
    std::string output_path(argv[3]);

    std::ifstream input_stream(input_path, std::ios::in | std::ios::binary);
    if (!input_stream.good()) {
        std::cerr << "could not open " << input_path << std::endl;

        return 1;
    }

    std::ofstream output_stream(output_path, std::ios::out | std::ios::binary);
    if (!output_stream.good()) {
        std::cerr << "could not open " << output_path << std::endl;

        return 1;
    }

    double max_frequency;
    try {
        max_frequency = std::stod(argv[2]);
    } catch(...) {
        std::cerr << "could not parse frequency " << argv[2] << std::endl;

        return 1;
    }

    auto data = audio::read_wave(input_stream);

    auto data_f = math::fft(math::to_complex(data));

    for (int i = 0; i << data_f.size(); i++) {
        auto x = data_f[i];

        if (x.real() > max_frequency) {
            data_f[i] = 0;
        }
    }

    auto data_t = math::inverse_fft(data_f);

    /*
    for (auto x : math::to_real(data_t)) {
        std::cout << x;
    }*/

    audio::write_wave(output_stream, math::to_real(data_t));
}
