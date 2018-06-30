#ifndef LOW_PASS_SRC_AUDIO_AUDIO_H_
#define LOW_PASS_SRC_AUDIO_AUDIO_H_

#define WAVEFILE_SAMPLE_RATE_OFFSET 24
#define WAVEFILE_SAMPLE_COUNT_OFFSET 40

#include <iostream>
#include <vector>

namespace audio {

class Wave {
 public:
  Wave() : header_(WAVEFILE_SAMPLE_COUNT_OFFSET) {}

  uint32_t SampleRate();
  uint32_t SampleCount();
  std::vector<int16_t> Samples();
  Wave& SetSamples(std::vector<int16_t>);

  friend std::istream& operator>>(std::istream&, Wave&);
  friend std::ostream& operator<<(std::ostream&, const Wave&);

 private:
  std::vector<char> header_;
  std::vector<int16_t> samples_;
};

}

#endif  // LOW_PASS_SRC_AUDIO_AUDIO_H_
