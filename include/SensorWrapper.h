#ifndef SENSOR_WRAPPER_H
#define SENSOR_WRAPPER_H


#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <iostream> // TODO: delete
using namespace std;

#include "GameObject.h"
#include "Goal.h"
#include "Ball.h"
#include "Robot.h"

class Match;

class SensorWrapper
{
public:
  SensorWrapper() : pov(-1) {}
  SensorWrapper(GameObject **, int, int = -1);
  SensorWrapper(vector<GameObject *> v, int pov_ = -1)
    { append(v); if(pov_ < robots.size() && pov_ >= -1) pov = pov_; else pov = -1; }
  SensorWrapper(vector<Ball *> b, vector<Goal *> g, vector<Robot *> r, int pov_ = -1)
    { append(b); append(g); append(r); if(pov_ < robots.size() && pov_ >= -1) pov = pov_; else pov = -1; }
  SensorWrapper(const SensorWrapper &);
  //SensorWrapper &operator=(const SensorWrapper &rhs) { clear(); *this = SensorWrapper(rhs); return *this; }
  // TODO: create new constructor for Sensor Fusion API
  // SensorWrapper(FusionSnapshot *);
  ~SensorWrapper();

  vector<Ball *> getBalls() const { return balls; }
  int getNumBalls() const { return balls.size(); }
  vector<Goal *> getGoals() const { return goals; }
  int getNumGoals() const { return goals.size(); }
  vector<Robot *> getRobots() const { return robots; }
  int getNumRobots() const { return robots.size(); }
  vector<Robot *> getRobots(Alliance);
  int getNumRobots(Alliance a) { return getRobots(a).size(); }
  int size() { return balls.size() + goals.size() + robots.size(); }

  Robot *getPOV() const { if(pov < robots.size() && pov >= 0) return robots[pov]; else return NULL; }
  bool POVExists() const { return getPOV() != NULL; }

  void push(GameObject *);
  void push_noclone(GameObject *);
  void append(vector<GameObject *>);
  void append(vector<Ball *>);
  void append(vector<Goal *>);
  void append(vector<Robot *>);
  void append(SensorWrapper s) { append(s.getBalls()); append(s.getGoals()); append(s.getRobots()); }
  // TODO: create append function to append directly from a fusion snapshot
  void clear();

  int findContained(GameObject *);
  int findContained(Ball *);
  int findContained(Goal *);
  int findContained(Robot *);

  string print();

  SensorWrapper &operator+(SensorWrapper &);
  SensorWrapper &operator+=(SensorWrapper &rhs) { append(rhs); return *this; }
  GameObject *operator[](int);
  operator string() { return print(); }

private:
  vector<Ball *> balls;
  vector<Goal *> goals;
  vector<Robot *> robots;

  int pov; // index of robot from which sensorwrapper is created

  friend class Match;
  friend class Robot;
};

#endif // SENSOR_WRAPPER_H
