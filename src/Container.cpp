#include "Container.h"

bool Container::pushBall(Ball *b)
{
  if(balls.size() < _size)
  {
    balls.push_back(b);
    b->x = x;
    b->y = y;
    return true;
  }
  return false;
}

Ball *Container::popBall()
{
  if(balls.size() == 0)
    return NULL;
  Ball *b = balls.front();
  balls.pop_front();
  return b;
}
