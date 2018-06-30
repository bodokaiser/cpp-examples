#ifndef LOW_PASS_SRC_AUDIO_AUDIO_H_
#define LOW_PASS_SRC_AUDIO_AUDIO_H_
#define WAVEFILE_HEADER_BYTES 40

#include <iostream>
#include <vector>

namespace audio {

class Wave {
 public:
  Wave() : header_(WAVEFILE_HEADER_BYTES) {}

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
