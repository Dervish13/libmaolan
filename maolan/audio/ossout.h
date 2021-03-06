/* vim: set syntax=cpp: */
#pragma once
#include <maolan/audio/input.h>
#include <maolan/audio/oss.h>
#include <string>


namespace maolan
{
namespace audio
{
class OSSOut : public OSS
{
public:
  OSSOut(const std::string &device, const std::size_t &channels);

  void connect(IO *to);
  void connect(IO *to, std::size_t inCh, std::size_t outCh);
  void fetch();
  void process();
  void convertToRaw();
  void play(int *frame, std::size_t dataSize);

protected:
  std::vector<Input> inputs;
};
} // namespace audio
} // namespace maolan
