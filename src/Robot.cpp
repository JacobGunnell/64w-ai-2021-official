#include "Robot.h"

SensorWrapper Robot::getViewableWrapper(GameObject **field, const int fieldLen)
{
  GameObject **visible = new GameObject *[fieldLen]; // allocate maximum possible memory requirement
  int writeidx = 0;
  for(int i = 0; i < fieldLen; i++)
  {
    double a1 = (PI*heading)/180 + (PI*_fov)/360;
    double a2 = (PI*heading)/180 - (PI*_fov)/360 - PI;
    if((field[i]->y*sin(a1) >= field[i]->x*cos(a1)) && (field[i]->y*sin(a2) >= field[i]->x*cos(a2))) // check if object is within fov
      visible[writeidx++] = field[i]; // add pointer to visible array
  }
  delete [] (visible + writeidx); // clear extra memory
  return SensorWrapper(visible, writeidx);
}
