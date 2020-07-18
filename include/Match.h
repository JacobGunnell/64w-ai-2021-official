#ifndef MATCH_H
#define MATCH_H


#include "Brain.h"

#include "GameObject.h"
#include "Robot.h"
#include "Ball.h"
#include "Goal.h"

#include <random>
#include <ctime>
using namespace std;

class Match
{
public:
  Match(Brain *, Brain *);
  Match() : Match(NULL, NULL) {}

  void setRed(Brain *r) { if(r != NULL) red = r; }
  Brain *getRed() const { return red; }
  void setBlue(Brain *b) { if(b != NULL) blue = b; }
  Brain *getBlue() const { return blue; }
  void setContestants(Brain *r, Brain *b) { setRed(r); setBlue(b); }

  Alliance run();
  int score(Alliance);
  void reset();

  static GameObject **defaultField();

  int wp, lp;

private:
  Brain *red;
  Brain *blue;
  GameObject **field;
};

#endif // MATCH_H
