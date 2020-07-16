#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <cmath>

class Ball;
class Goal;
class Robot;

class GameObject
{
public:
  GameObject(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

  double distFrom(int, int);
  double distFrom(GameObject g) { return distFrom(g.x, g.y); }

  static GameObject **defaultField();

  double x, y; // cartesian coords in inches, with (0,0) as the middle of the field
};

#include "Ball.h"
#include "Goal.h"
#include "Robot.h"

#endif // GAMEOBJECT_H
