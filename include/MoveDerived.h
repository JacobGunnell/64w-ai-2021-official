#ifndef MOVEDERIVED_H
#define MOVEDERIVED_H


#include "Goal.h"
#include "Ball.h"
#include "Robot.h"
#include "Move.h"

class Cycle : public Move
{
public:
  Cycle(Goal *goal_) : Move(), goal(goal_) {}

  MoveData getData(Robot *) override;
  bool execute() override;
  bool vexecute(Robot *) override;

  Cycle *clone() override { return new Cycle(*this); }

  Goal *goal;
};

class Intake : public Move
{
public:
  Intake(Ball *ball_) : Move(), ball(ball_) {}

  MoveData getData(Robot *) override;
  bool execute() override;
  bool vexecute(Robot *) override;

  Intake *clone() override { return new Intake(*this); }

  Ball *ball;
};

class ConnectRow : public Move
{
public:
  ConnectRow(int, Goal *[9]);

  MoveData getData(Robot *) override;
  bool execute() override;
  bool vexecute(Robot *) override;

  ConnectRow *clone() override { return new ConnectRow(*this); }

  int row;
  static const int NUM_GOALS = 3;
  Goal *goals[NUM_GOALS];
};

class ZeroMove : public Move
{
public:
  ZeroMove() : Move() {}

  MoveData getData(Robot *) override { return MoveData(); }
  bool execute() override;
  bool vexecute(Robot *) override { return true; }

  ZeroMove *clone() override { return new ZeroMove(*this); }
};

#endif // MOVEDERIVED_H
