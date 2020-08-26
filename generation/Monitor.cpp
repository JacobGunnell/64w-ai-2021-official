#include "Monitor.h"

string Monitor::print()
{
  stringstream s;
  s << endl
    << ":begin" << endl
    << gen << endl
    << wp << endl
    << lp << endl
    << rw << endl
    << bw << endl
    << numGames << endl
    << ms << endl
    << ":end" << endl;
  return s.str();
}

string Monitor::finish()
{
  stringstream s;
  s << endl
    << ":done" << endl;
  return s.str();
}
