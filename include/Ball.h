#ifndef BALL_H
#define BALL_H


#include "GameObject.h"

enum Color {RED=0, BLUE=1, NONE=-1};

class Ball : public GameObject
{
public:
  Ball(double xcoord, double ycoord, Color color) : GameObject(xcoord, ycoord), _color(color) {}
  Ball(Color color) : Ball(0, 0, color) {}

  Color getColor() const { return _color; }

private:
  Color _color;
};

#endif // BALL_H
