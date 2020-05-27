#include "Match.h"

Match::Match(Brain *redBrain, Brain *blueBrain)
{
    red = redBrain;
    blue = blueBrain;
    wp = 0;
    lp = 0;
}

int Match::run()
{
    // simulate a match
    wp = 5;
    lp = 4;
    return rand()%2;
}
