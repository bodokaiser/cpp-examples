#ifndef LOW_PASS_SRC_AUDIO_AUDIO_H_
#define LOW_PASS_SRC_AUDIO_AUDIO_H_

#include <iostream>
#include <vector>

namespace audio {

std::vector<int16_t> read_wave(std::istream&);
void write_wave(std::ostream&, std::vector<int16_t>);

}

#endif  // LOW_PASS_SRC_AUDIO_AUDIO_H_
