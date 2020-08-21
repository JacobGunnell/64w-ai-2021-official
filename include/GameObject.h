#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <typeinfo>
using namespace std;

#include <cmath>

class GameObject
{
public:
  GameObject(double xCoord, double yCoord) : GameObject(xCoord, yCoord, 0) {}
  GameObject(double xCoord, double yCoord, double timeSinceLastSeen) : x(xCoord), y(yCoord), lastSeen(timeSinceLastSeen) {}
  virtual ~GameObject() {}

  void moveTo(double x_, double y_) { x = x_; y = y_; }
  void moveTo(GameObject &g) { moveTo(g.x, g.y); }

  virtual GameObject *clone() = 0;

  double distFrom(int xCoord, int yCoord) { return sqrt((x - xCoord)*(x - xCoord) + (y - yCoord)*(y - yCoord)); }
  double distFrom(GameObject &g) { return distFrom(g.x, g.y); }

  virtual bool operator==(GameObject &rhs) { return (typeid(*this) == typeid(rhs)) && (distFrom(rhs) < obj_tolerance); } // TODO
  static constexpr double obj_tolerance = .5; // tolerance in inches for two GameObjects (seen in different snapshots) to be considered the same

  double x, y; // cartesian coords in inches, with (0,0) as the middle of the field
  double lastSeen;
};

#endif // GAMEOBJECT_H
