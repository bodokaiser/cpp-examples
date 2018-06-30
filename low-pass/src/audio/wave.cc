#include "audio/audio.h"

namespace audio {

std::vector<int16_t> Wave::Samples() {
    return samples_;
}

Wave& Wave::SetSamples(std::vector<int16_t> samples) {
  samples_ = samples;

  return *this;
}

std::istream& operator>>(std::istream& stream, Wave& wave) {
  uint32_t size;

  stream.read(wave.header_.data(), wave.header_.size());
  stream.read(reinterpret_cast<char*>(&size), sizeof(size));

  wave.samples_.resize(size);

  stream.read(reinterpret_cast<char*>(wave.samples_.data()),
      size * sizeof(int16_t));

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Wave& wave) {
  uint32_t size(wave.samples_.size());

  stream.write(wave.header_.data(), wave.header_.size());
  stream.write(reinterpret_cast<const char*>(&size), sizeof(size));

  stream.write(reinterpret_cast<const char*>(wave.samples_.data()),
      size * sizeof(int16_t));

  return stream;
}

}
