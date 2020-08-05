#ifndef MATCH_H
#define MATCH_H


#include "Brain.h"

#include "GameObject.h"
#include "Robot.h"
#include "Ball.h"
#include "Goal.h"

#include "MoveContainer.h"

#include <random>
#include <ctime>
#include <chrono>
using namespace std;

class Match
{
public:
  Match(Brain, Brain);
  Match(const Match &);
  ~Match();

  void setRed(Brain r) { red = r; }
  Brain getRed() const { return red; }
  void setBlue(Brain b) { blue = b; }
  Brain getBlue() const { return blue; }
  void setContestants(Brain r, Brain b) { setRed(r); setBlue(b); }

  Alliance run();
  int score(Alliance);
  void reset();

  int wp, lp;

private:
  Brain red;
  Brain blue;
  GameObject **field;
  int fieldSize;
  default_random_engine generator;

  double makemove(Robot **, Brain &, double);

  static GameObject **defaultField();
  static const int defaultFieldSize;
  static Goal **getGoals(GameObject **f) { return reinterpret_cast<Goal **>(f); }
  static const int numGoals;
  static Robot **getRobots(GameObject **f) { return reinterpret_cast<Robot **>(f + numGoals); }
  static const int numRobots;
  static Robot **getRedRobots(GameObject **f) { return reinterpret_cast<Robot **>(f + numGoals); }
  static const int numRedRobots;
  static Robot **getBlueRobots(GameObject **f) { return reinterpret_cast<Robot **>(f + numGoals + numRedRobots); }
  static const int numBlueRobots;
  static Ball **getBalls(GameObject **f) { return reinterpret_cast<Ball **>(f + numGoals + numRobots); }
  static const int numBalls;
};

#endif // MATCH_H
