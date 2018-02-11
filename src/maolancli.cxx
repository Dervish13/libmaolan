#include <iostream>
#include <maolan/audiofileinput>
#include <maolan/audioossout>
#include <maolan/audioossin>
#include <maolan/audiotrack>
#include <maolan/config>


using namespace std;


int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <wav file>" << endl;
    return 1;
  }
  cout << "Using " << argv[1] << " as input file" << endl;
  AudioOSSIn in(1);
  AudioFileInput infile(argv[1]);
  AudioOSSOut out(1);
  out.connect(&in);
  out.connect(&infile);
  cout << "Playing ..." << endl;
  while (true)
  {
    for (auto &io : AudioIO::ios)
    {
      cout << "Fetching " << io->name;
      io->fetch();
      cout << endl;
      cout << "Processing " << io->name;
      io->process();
      cout << endl;
    }
  }
  cout << endl;
  return 0;
}
