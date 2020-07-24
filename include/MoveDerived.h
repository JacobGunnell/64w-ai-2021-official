#ifndef MOVEDERIVED_H
#define MOVEDERIVED_H


#include "Goal.h"
#include "Ball.h"
#include "Move.h"
#include "Robot.h"

class Cycle : public Move
{
public:
  Cycle(Goal *goal_) : Move(), goal(goal_) {}

  colvec vectorize();
  bool execute();
  bool vexecute(Robot *);

  Goal *goal;
};

class Intake : public Move
{
public:
  Intake(Ball *ball_) : Move(), ball(ball_) {}

  colvec vectorize();
  bool execute();
  bool vexecute(Robot *);

  Ball *ball;
};

#endif // MOVEDERIVED_H
