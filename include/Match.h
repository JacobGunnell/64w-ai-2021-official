#ifndef MATCH_H
#define MATCH_H


#include "Brain.h"

#include <random>
#include <ctime>
using namespace std;

class Match
{
public:
    Match(Brain *, Brain *);

    int run();

    int wp, lp;

private:
    Brain *red;
    Brain *blue;
};

#endif // MATCH_H
