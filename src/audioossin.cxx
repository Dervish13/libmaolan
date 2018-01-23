#include <iostream>
#include <cstring>
#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <maolan/audioossin>
#include <maolan/config>


using namespace std;


AudioOSSIn::AudioOSSIn(const size_t &channels)
  : AudioIO(channels)
{
  rawData = new int[channels * Config::audioChunkSize];
  string device = "/dev/dsp";
  format = AFMT_S32_NE;
  samplerate = 88200;
  if((fd = open(device.data(), O_RDONLY, 0)) == -1)
  {
    cerr << device << ' ' << strerror(errno) << endl;
    exit(1);
  }
  int tmp = format;
  if(ioctl(fd, SNDCTL_DSP_SETFMT, &tmp) == -1 || tmp != format)
  {
    cerr << "Setting audio format failed " << strerror(errno) << endl;
    exit(1);
  }
  tmp = channels;
  if(ioctl(fd, SNDCTL_DSP_CHANNELS, &tmp) == -1 || tmp != channels)
  {
    cerr << "Can not set number of channels to " << channels;
    cerr << ": " << strerror(errno) << endl;
    exit(1);
  }
  tmp = samplerate;
  if(ioctl(fd, SNDCTL_DSP_SPEED, &tmp) == -1 || tmp != samplerate)
  {
    cerr << "Can not set sampling frequency to " << samplerate << ": ";
    cerr << strerror(errno) << endl;
    exit(1);
  }
}


AudioOSSIn::~AudioOSSIn()
{
  close(fd);
  delete []rawData;
}


void AudioOSSIn::fetch()
{
  int dataSize = channels() * Config::audioChunkSize * sizeof(rawData[0]);
  read(fd, rawData, dataSize);
}


void AudioOSSIn::process()
{
  for (int j = 0; j < channels(); ++j)
  {
    outputs[j] = AudioChunk(new AudioChunkData(Config::audioChunkSize));
    for (int i = 0; i < Config::audioChunkSize; ++i)
    {
      outputs[j]->data[i] = rawData[i * channels() + j];

    }
  }
}


size_t AudioOSSIn::channels() const
{
  return outputs.size();
}
