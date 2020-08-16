#include "Container.h"

Container::Container(const Container &cpy) : GameObject(cpy.x, cpy.y)
{
  for(deque<Ball *>::const_iterator it = cpy.balls.begin(); it != cpy.balls.end(); ++it)
    balls.push_back((*it)->clone());
}

deque<Ball *> Container::dump()
{
  deque<Ball *> temp = balls;
  balls.clear();
  return temp;
}

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

int Container::numBalls(Color c)
{
  int n = 0;
  for(deque<Ball *>::iterator it = balls.begin(); it != balls.end(); ++it)
    n += ((*it)->getColor() == c);
  return n;
}
