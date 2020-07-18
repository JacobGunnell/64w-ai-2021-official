#ifndef GOAL_H
#define GOAL_H


#include "Container.h"
#include "Ball.h"
#include <deque>
using namespace std;

class Goal : public Container
{
public:
  Goal(double xcoord, double ycoord, Ball *b1, Ball *b2, Ball *b3) : Container(xcoord, ycoord, 3) { balls.push_back(b1); balls.push_back(b2); balls.push_back(b3); }
  Goal(double xcoord, double ycoord, Ball *b1, Ball *b2) : Container(xcoord, ycoord, 3) { balls.push_back(b1); balls.push_back(b2); }
  Goal(double xcoord, double ycoord, Ball *b1) : Container(xcoord, ycoord, 3) { balls.push_back(b1); }
  Goal(double xcoord, double ycoord) : Container(xcoord, ycoord, 3) {}

  Ball *top() { if(balls.size() > 0) return balls.back(); return NULL; }
};

#endif // GOAL_H
