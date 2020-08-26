#ifndef MONITOR_H
#define MONITOR_H


#include <string>
#include <sstream>
using namespace std;

struct Monitor
{
  string print();

  static string finish();

  int gen = -1;
  int wp = 0;
  int lp = 0;
  int rw = 0;
  int bw = 0;
  int ms = 0;
  int numGames = 0;
};

#endif // MONITOR_H
