#ifndef SENSOR_WRAPPER_H
#define SENSOR_WRAPPER_H


#include "GameObject.h"

class SensorWrapper
{
public:
  SensorWrapper(GameObject **objs_, int numObjs_) : objs(objs_), numObjs(numObjs_) {}
  // TODO: create new constructor for Sensor Fusion API
  // SensorWrapper(FusionSnapshot *);
  ~SensorWrapper() { delete objs; }

  GameObject **getObjs() const { return objs; }
  int getNumObjs() const { return numObjs; }

private:
  GameObject **objs;
  int numObjs;
};

#endif // SENSOR_WRAPPER_H
