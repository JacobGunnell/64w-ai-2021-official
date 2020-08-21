#ifndef MOVEDERIVED_H
#define MOVEDERIVED_H


#include <iostream> // TODO: remove
using namespace std;

#include "Goal.h"
#include "Ball.h"
#include "Robot.h"
#include "Move.h"

class Claim : public Move
{
public:
  Claim(Goal *goal_) : Move(), goal(goal_) {}

  MoveData getData(SensorWrapper &) override;
  bool execute() override;
  bool vexecute(SensorWrapper &) override;
  bool viable(SensorWrapper &) override;

  Claim *clone() override { return new Claim(*this); }

  Goal *goal;
};

class Cycle : public Move
{
public:
  Cycle(Goal *goal_) : Move(), goal(goal_) {}

  MoveData getData(SensorWrapper &) override;
  bool execute() override;
  bool vexecute(SensorWrapper &) override;
  bool viable(SensorWrapper &) override;

  Cycle *clone() override { return new Cycle(*this); }

  Goal *goal;
};

class Intake : public Move
{
public:
  Intake(Ball *ball_) : Move(), ball(ball_) {}

  MoveData getData(SensorWrapper &) override;
  bool execute() override;
  bool vexecute(SensorWrapper &) override;
  bool viable(SensorWrapper &) override;

  Intake *clone() override { return new Intake(*this); }

  Ball *ball;
};

class ZeroMove : public Move
{
public:
  ZeroMove() : Move() {}

  MoveData getData(SensorWrapper &) override { return MoveData(); }
  bool execute() override;
  bool vexecute(SensorWrapper &) override { return true; }
  bool viable(SensorWrapper &) override { return true; }

  ZeroMove *clone() override { return new ZeroMove(*this); }
};

#endif // MOVEDERIVED_H
