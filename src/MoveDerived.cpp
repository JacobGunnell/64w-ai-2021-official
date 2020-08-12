#ifndef GENERATION_NO_ROBOT
#include "Hardware.h"
#endif
#include "MoveDerived.h"

MoveData Cycle::getData(Robot *robot)
{
  if(robot == NULL)
    return MoveData();

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
  if(robot == NULL)
    return MoveData();

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

ConnectRow::ConnectRow(int row_, Goal **goals_) : Move(), row(row_)
{
  Goal *g;
  if(goals_ != NULL)
    for(int i = 0; i < NUM_GOALS; i++)
      if((g = goals_[Goal::connectableRowIndices[row][i]]) != NULL)
        goals[i] = g;
}

MoveData ConnectRow::getData(Robot *robot)
{
  if(robot == NULL)
    return MoveData();

  int x = robot->x;
  int y = robot->y;

  // Try it forwards (i.e. 0 - 4 - 8)
  MoveData mForward;
  for(int i = 0; i < NUM_GOALS; i++)
  {
    mForward += Cycle(goals[i]).getData(robot); // claiming a row requires cycling each of its goals
    robot->moveTo(goals[i]);
  }
  robot->moveTo(x, y);

  // Try it backwards (i.e. 8 - 4 - 0)
  MoveData mBackward;
  for(int i = NUM_GOALS - 1; i >= 0; i++)
  {
    mBackward += Cycle(goals[i]).getData(robot); // claiming a row requires cycling each of its goals
    robot->moveTo(goals[i]);
  }
  robot->moveTo(x, y);

  return mForward.t < mBackward.t ? mForward : mBackward; // return the shorter (time-wise) of the two
}

bool ConnectRow::vexecute(Robot *robot) // TODO
{

}


#ifndef GENERATION_NO_ROBOT
// Instructions for execution with a physical robot via okapilib (TODO)

bool Cycle::execute()
{

}

bool Intake::execute()
{

}

bool ConnectRow::execute()
{

}

bool ZeroMove::execute() { return true; }

#else
// Empty function definitions so that my gcc linker doesn't throw a fit when i build generation.exe
// Just add one of these for every one of those ^

bool Cycle::execute() { return false; }
bool Intake::execute() { return false; }
bool ConnectRow::execute() { return false; }
bool ZeroMove::execute() { return false; }

#endif
