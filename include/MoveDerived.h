#ifndef MOVEDERIVED_H
#define MOVEDERIVED_H


#ifndef GENERATION_NO_ROBOT
#include "Hardware.h"
#endif
#include "Goal.h"
#include "Ball.h"
#include "Move.h"
#include "Robot.h"

class Cycle : public Move
{
public:
  Cycle(Goal *goal_) : Move(), goal(goal_) {}

  MoveData getData(Robot *) override;
  bool execute() override;
  bool vexecute(Robot *) override;

  Goal *goal;
};

class Intake : public Move
{
public:
  Intake(Ball *ball_) : Move(), ball(ball_) {}

  MoveData getData(Robot *) override;
  bool execute() override;
  bool vexecute(Robot *) override;

  Ball *ball;
};

class ConnectRow : public Move
{
public:
  ConnectRow(int, Goal *[9]);

  MoveData getData(Robot *) override;
  bool execute() override;
  bool vexecute(Robot *) override;

  int row;
  static const int NUM_GOALS = 3;
  Goal *goals[NUM_GOALS];
};

#endif // MOVEDERIVED_H
