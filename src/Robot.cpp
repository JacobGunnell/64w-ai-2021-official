#include "Robot.h"

SensorWrapper Robot::getViewableWrapper(GameObject **field, const int fieldLen)
{
  GameObject **visible = new GameObject *[fieldLen]; // allocate maximum possible memory requirement
  int writeidx = 0;
  for(int i = 0; i < fieldLen; i++)
  {
    double a1 = (PI*heading)/180 + (PI*_fov)/360;
    double a2 = (PI*heading)/180 - (PI*_fov)/360 - PI;
    double dx = field[i]->x - x;
    double dy = field[i]->y - y;
    if((dy*sin(a1) >= dx*cos(a1)) && (dy*sin(a2) >= dx*cos(a2))) // check if object is within fov
      visible[writeidx++] = field[i]; // add pointer to visible array
  }
  SensorWrapper s(visible, writeidx);
  delete [] visible;
  return s;
}
