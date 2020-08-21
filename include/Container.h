#ifndef CONTAINER_H
#define CONTAINER_H


#include "GameObject.h"
#include "Ball.h"
#include <list>
using namespace std;

class Container : public GameObject
{
public:
  Container(double xcoord, double ycoord, int size) : GameObject(xcoord, ycoord), _size(size) {}
  Container(const Container &);
  virtual ~Container() {}

  list<Ball *> &getBalls() { return balls; }
  list<Ball *> &dump();
  int numBalls() { return balls.size(); }
  int containerSize() const { return _size; }
  bool full() const { return balls.size() == _size; }
  bool empty() const { return balls.size() == 0; }
  virtual bool pushBall(Ball *); // push to the top of the container (back of list)
  virtual Ball *popBall(); // pop from the bottom of the container (front of list)
  int numBalls(Color);

protected:
  list<Ball *> balls;

private:
  int _size;
};

#endif // CONTAINER_H
