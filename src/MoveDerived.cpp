#include "MoveDerived.h"

MoveData Cycle::getData(Robot *robot)
{
  Color c = static_cast<Color>(robot->getAlliance());
  MoveData m;
  int ourTotalBalls = robot->numBalls(c) + goal->numBalls(c);
  int goalSize = goal->containerSize();
  m.p = goal->numBalls(!c) + (ourTotalBalls > goalSize ? goalSize : ourTotalBalls); // number of opponent balls descored + (number of our balls scored up to 3)
  m.t = (goal->distFrom(*robot) / robot->avgSpeed); // TODO: implement better time factor estimate
  m.r = 1; // TODO: r value
  return m;
}

bool Cycle::vexecute(Robot *robot)
{
  Color c = static_cast<Color>(robot->getAlliance());
  int ourTotalBalls = robot->numBalls(c) + goal->numBalls(c);
  robot->moveTo(goal);
}

MoveData Intake::getData(Robot *robot)
{
  MoveData m;
  m.p = 0;
  m.t = ball->distFrom(*robot) / robot->avgSpeed; // TODO: implement better time factor estimate
  m.r = 1; // TODO: r value
  return m;
}

bool Intake::vexecute(Robot *robot)
{
  robot->moveTo(ball);
  return robot->pushBall(ball);
}


#ifndef GENERATION_NO_ROBOT
// Instructions for execution with a physical robot via okapilib

bool Cycle::execute()
{

}

bool Intake::execute()
{

}

#else
// Empty function definitions so that my gcc linker doesn't throw a fit when i build generation.exe
// Just add one of these for every one of those ^

bool Cycle::execute() { return false; }
bool Intake::execute() { return false; }

#endif
