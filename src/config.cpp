#include <maolan/config.h>

using namespace maolan;

size_t Config::audioBufferSize = 0;
int Config::samplerate = 48000;
int Config::bpm = 120;
std::vector<BPM> Config::bpms;
