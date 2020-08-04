#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <cmath>

class GameObject
{
public:
  GameObject(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}
  virtual ~GameObject() = default;

  virtual GameObject *clone() { return new GameObject(*this); }

  double distFrom(int xCoord, int yCoord) { return sqrt((x - xCoord)*(x - xCoord) + (y - yCoord)*(y - yCoord)); }
  double distFrom(GameObject g) { return distFrom(g.x, g.y); }

  double x, y; // cartesian coords in inches, with (0,0) as the middle of the field
};

#endif // GAMEOBJECT_H
