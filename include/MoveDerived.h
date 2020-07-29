#ifndef MOVEDERIVED_H
#define MOVEDERIVED_H


#include "Hardware.h"
#include "Goal.h"
#include "Ball.h"
#include "Move.h"
#include "Robot.h"

class Cycle : public Move
{
public:
  Cycle(Goal *goal_) : Move(), goal(goal_) {}

  MoveData getData() override;
  bool execute() override;
  bool vexecute(Robot *) override;

  Goal *goal;
};

class Intake : public Move
{
public:
  Intake(Ball *ball_) : Move(), ball(ball_) {}

  MoveData getData() override;
  bool execute() override;
  bool vexecute(Robot *) override;

  Ball *ball;
};

#endif // MOVEDERIVED_H
