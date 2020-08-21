#include "Robot.h"

Alliance operator!(const Alliance &a)
{
  if(a == RED_ALLIANCE)
    return BLUE_ALLIANCE;
  else if(a == BLUE_ALLIANCE)
    return RED_ALLIANCE;
  else
    return NEITHER_ALLIANCE;
}

bool Robot::pushBall(Ball *b)
{
  if(Container::pushBall(b))
  {
    if(b->getColor() != static_cast<Color>(_alliance))
      ejectBall(0);
    return true;
  }
  else
    return false;
}

bool Robot::ejectBall(int idx)
{
  if(idx >= 0 && idx < balls.size())
  {
    const double EJECTION_DISTANCE = 12.0; // inches behind the robot
    list<Ball *>::iterator it = balls.begin();
    advance(it, idx);
    (*it)->setX(getX() - EJECTION_DISTANCE*sin(heading));
    (*it)->setY(getY() - EJECTION_DISTANCE*cos(heading));
    balls.erase(it);
    return true;
  }
  else
    return false;
}

SensorWrapper &Robot::getViewableWrapper(GameObject **field, const int fieldLen)
{
  GameObject **visible = new GameObject *[fieldLen]; // allocate maximum possible memory requirement
  int writeidx = 0;
  for(int i = 0; i < fieldLen; i++)
  {
    if(field[i] != NULL)
    {
      double a1 = (PI*heading)/180 + (PI*_fov)/360;
      double a2 = (PI*heading)/180 - (PI*_fov)/360 - PI;
      double dx = field[i]->getX() - getX();
      double dy = field[i]->getY() - getY();
      if((dy*sin(a1) >= dx*cos(a1)) && (dy*sin(a2) >= dx*cos(a2))) // check if object is within fov
        visible[writeidx++] = field[i]->clone(); // add pointer to visible array
    }
  }
  static SensorWrapper s(visible, writeidx);
  s.pov = s.findContained(this);
  delete [] visible;
  return s;
}

SensorWrapper &Robot::getViewableWrapper(SensorWrapper &s)
{
  static SensorWrapper visible;
  for(int i = 0; i < s.size(); i++)
  {
    if(s[i] != NULL)
    {
      double a1 = (PI*heading)/180 + (PI*_fov)/360;
      double a2 = (PI*heading)/180 - (PI*_fov)/360 - PI;
      double dx = s[i]->getX() - getX();
      double dy = s[i]->getY() - getY();
      if((dy*sin(a1) >= dx*cos(a1)) && (dy*sin(a2) >= dx*cos(a2))) // check if object is within fov
        visible.push(s[i]); // add pointer to visible array
    }
  }
  return visible;
}
