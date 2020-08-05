#ifndef SENSOR_WRAPPER_H
#define SENSOR_WRAPPER_H


#include "GameObject.h"
#include "Goal.h"
#include "Ball.h"

class SensorWrapper
{
public:
  SensorWrapper(GameObject **, int);
  SensorWrapper(const SensorWrapper &);
  // TODO: create new constructor for Sensor Fusion API
  // SensorWrapper(FusionSnapshot *);
  ~SensorWrapper();

  GameObject **getObjs() const { return objs; }
  int getNumObjs() const { return numObjs; }

  SensorWrapper operator+(SensorWrapper);

private:
  GameObject **objs;
  int numObjs;
};

#endif // SENSOR_WRAPPER_H
