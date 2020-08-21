#include "Container.h"

Container::Container(const Container &cpy) : GameObject(cpy.getX(), cpy.getY())
{
  for(list<Ball *>::const_iterator it = cpy.balls.begin(); it != cpy.balls.end(); ++it)
    balls.push_back((*it)->clone());
}

list<Ball *> &Container::dump()
{
  static list<Ball *> temp = balls;
  balls.clear();
  return temp;
}

bool Container::pushBall(Ball *b)
{
  if(balls.size() < _size && b != NULL)
  {
    balls.push_back(b);
    b->setX(getX());
    b->setY(getY());
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
  for(list<Ball *>::iterator it = balls.begin(); it != balls.end(); ++it)
    if(*it != NULL && (*it)->getColor() == c)
      n++;
  return n;
}
