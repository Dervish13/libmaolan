#include <maolan/audio/connection.h>


using namespace maolan::audio;


Connection::Connection() {}


Connection::Connection(IO *connectTo, size_t &ch) { target(connectTo, ch); }


void Connection::target(IO *connectTo, size_t &ch)
{
  to = connectTo;
  channel = ch;
}


Buffer Connection::pull() { return to->pull(channel); }


IO *Connection::get() { return to; }
