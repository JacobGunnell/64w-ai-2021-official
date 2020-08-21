#ifndef GOAL_H
#define GOAL_H


#include "Container.h"
#include "Ball.h"

class Goal final : public Container
{
public:
  Goal(double xcoord, double ycoord, Ball *b1, Ball *b2, Ball *b3) : Container(xcoord, ycoord, 3) { pushBall(b1); pushBall(b2); pushBall(b3); }
  Goal(double xcoord, double ycoord, Ball *b1, Ball *b2) : Container(xcoord, ycoord, 3) { pushBall(b1); pushBall(b2); }
  Goal(double xcoord, double ycoord, Ball *b1) : Container(xcoord, ycoord, 3) { pushBall(b1); }
  Goal(double xcoord, double ycoord) : Container(xcoord, ycoord, 3) {}

  Goal *clone() override { return new Goal(*this); }

  Ball *top() { if(!balls.empty()) return balls.back(); else return NULL; }
  Color topColor() { Ball *t = top(); if(t != NULL) return t->getColor(); else return NONE; }

  static const int connectableRowIndices[8][3];
};

#endif // GOAL_H
