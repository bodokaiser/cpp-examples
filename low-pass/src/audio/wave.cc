#include "audio/audio.h"

namespace audio {

std::vector<int16_t> read_wave(std::istream& istream) {
    uint32_t size;

    istream.ignore(40);
    istream.read(reinterpret_cast<char*>(&size), sizeof(size));

    std::vector<int16_t> samples(size);

    istream.read(reinterpret_cast<char*>(samples.data()), size);

    return samples;
}

void write_wave(std::ostream& ostream, std::vector<int16_t> samples) {
    ostream.write(reinterpret_cast<char*>(samples.size()),
        sizeof(samples.size()));

    for (int i = 0; i < 40; i++) {
        ostream.put(0);
    }

    ostream.write(reinterpret_cast<char*>(samples.data()), samples.size());
}

}
