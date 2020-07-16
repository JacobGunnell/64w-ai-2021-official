#ifndef CONTAINER_H
#define CONTAINER_H


#include "GameObject.h"
#include "Ball.h"
#include <deque>

class Container : public GameObject
{
public:
  Container(double xcoord, double ycoord, int size) : GameObject(xcoord, ycoord), _size(size) {}

  deque<Ball *> getBalls() const { return balls; }
  bool pushBall(Ball *); // push to the top of the container (back of list)
  Ball *popBall(); // pop from the bottom of the container (front of list)

protected:
  deque<Ball *> balls;

private:
  int _size;
};

#endif // CONTAINER_H
