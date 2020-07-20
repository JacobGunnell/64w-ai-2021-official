#include "Goal.h"

int Goal::numBalls(Color c)
{
  int n = 0;
  for(deque<Ball *>::iterator it = balls.begin(); it != balls.end(); it++)
    n += ((*it)->getColor() == c);
  return n;
}
