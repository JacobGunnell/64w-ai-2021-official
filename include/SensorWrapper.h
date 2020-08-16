#ifndef SENSOR_WRAPPER_H
#define SENSOR_WRAPPER_H


#include <vector>
#include <typeinfo>
using namespace std;

#include "GameObject.h"
#include "Goal.h"
#include "Ball.h"
#include "Robot.h"

class SensorWrapper
{
public:
  SensorWrapper() : SensorWrapper(NULL, 0) {}
  SensorWrapper(GameObject **, int);
  SensorWrapper(vector<GameObject *> v) { append(v); }
  SensorWrapper(vector<Ball *> b, vector<Goal *> g, vector<Robot *> r) { append(b); append(g); append(r); }
  SensorWrapper(const SensorWrapper &cpy) : SensorWrapper(cpy.balls, cpy.goals, cpy.robots) {}
  // TODO: create new constructor for Sensor Fusion API
  // SensorWrapper(FusionSnapshot *);
  ~SensorWrapper();

  vector<Ball *> getBalls() const { return balls; }
  int getNumBalls() const { return balls.size(); }
  vector<Goal *> getGoals() const { return goals; }
  int getNumGoals() const { return goals.size(); }
  vector<Robot *> getRobots() const { return robots; }
  int getNumRobots() const { return robots.size(); }
  int size() const { return balls.size() + goals.size() + robots.size(); }

  void push(GameObject *);
  void append(vector<GameObject *>);
  void append(vector<Ball *>);
  void append(vector<Goal *>);
  void append(vector<Robot *>);
  void append(SensorWrapper s) { append(s.getBalls()); append(s.getGoals()); append(s.getRobots()); }
  // TODO: create append function to append directly from a fusion snapshot

  SensorWrapper operator+(SensorWrapper);
  GameObject *operator[](int);

private:
  vector<Ball *> balls;
  vector<Goal *> goals;
  vector<Robot *> robots;
};

#endif // SENSOR_WRAPPER_H
