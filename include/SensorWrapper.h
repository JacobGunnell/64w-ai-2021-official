#ifndef SENSOR_WRAPPER_H
#define SENSOR_WRAPPER_H


#include <vector>
using namespace std;

#include "GameObject.h"
#include "Goal.h"
#include "Ball.h"

class SensorWrapper
{
public:
  SensorWrapper() : SensorWrapper(NULL, 0) {}
  SensorWrapper(GameObject **, int);
  SensorWrapper(vector<GameObject *> v) : SensorWrapper(v.data(), v.size()) {}
  SensorWrapper(const SensorWrapper &cpy) : SensorWrapper(cpy.objs) {}
  // TODO: create new constructor for Sensor Fusion API
  // SensorWrapper(FusionSnapshot *);
  ~SensorWrapper();

  vector<GameObject *> getObjs() const { return objs; }
  int getNumObjs() const { return objs.size(); }

  void push(GameObject *);
  void append(vector<GameObject *>);
  void append(SensorWrapper s) { append(s.getObjs()); }
  // TODO: create append function to append directly from a fusion snapshot

  SensorWrapper operator+(SensorWrapper);
  GameObject *operator[](int i) { if(i >= 0 && i < objs.size()) return objs[i]; else return NULL; }

private:
  vector<GameObject *> objs;
};

#endif // SENSOR_WRAPPER_H
