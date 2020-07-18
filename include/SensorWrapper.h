#ifndef SENSOR_WRAPPER_H
#define SENSOR_WRAPPER_H


#include "GameObject.h"
#include "Ball.h"
#include "Goal.h"
#include "Robot.h"

class SensorWrapper
{
public:
  SensorWrapper() {}
  // TODO: create new constructor for Sensor Fusion API
  // SensorWrapper(FusionSnapshot *);

  GameObject **getObjs() const { return objs; }
  int getNumObjs() const { return numObjs; }

private:
  GameObject **objs;
  int numObjs;

  friend SensorWrapper Robot::getViewableWrapper(GameObject **);
};

#endif // SENSOR_WRAPPER_H
