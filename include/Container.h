#ifndef CONTAINER_H
#define CONTAINER_H


#include "GameObject.h"
#include "Ball.h"
#include <deque>
using namespace std;

class Container : public GameObject
{
public:
  Container(double xcoord, double ycoord, int size) : GameObject(xcoord, ycoord), _size(size) {}
  Container(const Container &);
  virtual ~Container() = default;

  deque<Ball *> getBalls() const { return balls; }
  deque<Ball *> dump();
  int numBalls() const { return balls.size(); }
  int containerSize() const { return _size; }
  bool full() const { return balls.size() == _size; }
  bool empty() const { return balls.size() == 0; }
  bool pushBall(Ball *); // push to the top of the container (back of list)
  Ball *popBall(); // pop from the bottom of the container (front of list)
  int numBalls(Color);

protected:
  deque<Ball *> balls;

private:
  int _size;
};

#endif // CONTAINER_H
