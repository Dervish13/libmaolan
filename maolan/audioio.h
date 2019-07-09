/* vim: set syntax=cpp: */
#pragma once
#include <string>
#include <vector>
#include <maolan/io.h>
#include <maolan/audiochunk.h>


namespace maolan
{
  namespace audio
  {
    class IO : public maolan::IO
    {
      public:
        IO(const size_t &outs = 0, bool front = false);
        ~IO();

        virtual std::size_t channels() const = 0;
        Chunk pull(const unsigned &channel);

      protected:
        std::vector<Chunk> outputs;
    };
  }
}
