#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <cmath>

enum ObjectType {BALL, ROBOT};

class GameObject
{
public:
  GameObject(int xCoord, int yCoord, ObjectType objType) : x(xCoord), y(yCoord), type(objType) {}

  double distFrom(int, int);
  double distFrom(GameObject g) { return distFrom(g.x, g.y); }

  double x, y; // cartesian coords in inches, with (0,0) as the middle of the field
  ObjectType type;
private:

};

#endif // GAMEOBJECT_H
