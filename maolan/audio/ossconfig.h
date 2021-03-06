/* vim: set syntax=cpp: */
#pragma once
#include <maolan/config.h>
#include <string>


namespace maolan
{
namespace audio
{
class OSSConfig : public Config
{
public:
  OSSConfig();

  int fd;
  int format;
  std::size_t audioChannels;
  std::size_t frag;
  std::size_t fragSize;
  std::size_t count;
  std::string device;
};
} // namespace audio
} // namespace maolan
