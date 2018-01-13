#pragma once
#include <string>
#include <vector>
#include <sndfile.hh>
#include "audioio.h"


class AudioFileInput : public AudioIO
{
  public:
    AudioFileInput(const std::string &path);
    ~AudioFileInput();

    static std::size_t size;

    void fetch();
    void split();
    std::size_t channels() const;

  protected:
    SndfileHandle audioFile;

  private:
    float *rawData;
};