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
  // This isn't totally true-to-life, but it's faster
  // Essentially all of our balls (up to 3) end up in the goal and the rest end up in the robot, and all of theirs end up on the ground somewhere
  Color c = static_cast<Color>(robot->getAlliance());
  int totalBalls = robot->numBalls() + goal->numBalls();
  int ourTotalBalls = robot->numBalls(c) + goal->numBalls(c);
  const int GOAL_CAPACITY = goal->containerSize();

  robot->moveTo(goal);

  // Dump / sort balls
  deque<Ball *> ourBalls, theirBalls;
  deque<Ball *> temp = goal->dump();
  for(deque<Ball *>::iterator it = temp.begin(); it != temp.end(); ++it)
  {
    if((*it)->getColor() == c)
      ourBalls.push_back(*it);
    else
      theirBalls.push_back(*it);
  }
  temp = robot->dump();
  for(deque<Ball *>::iterator it = temp.begin(); it != temp.end(); ++it)
  {
    if((*it)->getColor() == c)
      ourBalls.push_back(*it);
    else
      theirBalls.push_back(*it);
  }

  // Put balls in the goal / robot
  if(ourBalls.size() <= GOAL_CAPACITY)
    for(deque<Ball *>::iterator it = ourBalls.begin(); it != ourBalls.end(); ++it)
      goal->pushBall(*it);
  else
  {
    deque<Ball *>::iterator it;
    for(it = ourBalls.begin(); it != ourBalls.begin() + GOAL_CAPACITY; ++it)
      goal->pushBall(*it);
    for( ; it != ourBalls.end(); ++it)
      robot->pushBall(*it);
  }

  // Scatter their balls elsewhere (TODO)
  //for(deque<Ball *>::iterator it = theirBalls.begin(); it != theirBalls.end(); ++it)

  return true; // TODO: are there any cases where this would fail?
}

bool Cycle::viable(Robot *robot)
{
  Color c = static_cast<Color>(robot->getAlliance());
  return goal->numBalls(!c) != 0 || // either the opposing alliance has some balls in the goal
    (!goal->full() && !robot->empty()); // or the goal is ours and we have more to score
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

bool Intake::viable(Robot *robot)
{
  return !robot->full();
}

/*
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
*/

#ifndef GENERATION_NO_ROBOT
// Instructions for execution with a physical robot via okapilib (TODO)

bool Cycle::execute()
{

}

bool Intake::execute()
{

}

bool ZeroMove::execute() { return true; }

#else
// Empty function definitions so that my gcc linker doesn't throw a fit when i build generation.exe
// Just add one of these for every one of those ^

bool Cycle::execute() { return false; }
bool Intake::execute() { return false; }
bool ZeroMove::execute() { return false; }

#endif
