#ifndef MATCH_H
#define MATCH_H


#include "Brain.h"

#include "GameObject.h"
#include "Robot.h"
#include "Ball.h"
#include "Goal.h"

#include "SensorWrapper.h"
#include "MoveContainer.h"

#include <random>
#include <ctime>
#include <chrono>
using namespace std;

class Match
{
public:
  Match(Brain *, Brain *);
  Match(const Match &);
  ~Match();

  void setRed(Brain *r) { if(r != NULL) red = r; }
  Brain *getRed() const { return red; }
  void setBlue(Brain *b) { if(b != NULL) blue = b; }
  Brain *getBlue() const { return blue; }
  void setContestants(Brain *r, Brain *b) { setRed(r); setBlue(b); }

  Alliance run();
  int score(Alliance a) { if(field != NULL) return score(*field, a); else return -1; }
  void reset();

  static int score(const SensorWrapper &, Alliance);

  int wp, lp;

private:
  Brain *red;
  Brain *blue;
  SensorWrapper *field;
  default_random_engine generator;

  double makemove(vector<Robot *>, Brain *, double);

  static SensorWrapper *defaultField();
};

#endif // MATCH_H
