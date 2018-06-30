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
  std::string output_path(argv[2]);

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

  audio::Wave wave;
  input_stream >> wave;

  auto sample_count = wave.SampleCount();
  auto sample_rate = wave.SampleRate();
  auto delta_frequency = 1. * sample_rate / sample_count;

  auto spectrum = math::fft(math::complex(wave.Samples()));

  for (size_t i = 25000; i < spectrum.size(); ++i) {
    spectrum[i] = 0;
  }

  auto audio = math::inverse_fft(spectrum);

  output_stream << wave.SetSamples(math::real<int16_t>(audio));
}
