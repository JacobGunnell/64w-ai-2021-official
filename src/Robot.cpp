#include "Robot.h"

SensorWrapper Robot::getViewableWrapper(GameObject **field)
{
  GameObject **visible = NULL; // TODO: implement
  SensorWrapper s;
  s.objs = visible;
  return s;
}
