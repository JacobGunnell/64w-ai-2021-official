#ifndef GENERATION_NO_ROBOT
#include "Hardware.h"
#endif
#include "MoveDerived.h"

MoveData Claim::getData(SensorWrapper &s)
{
  Robot *robot = s.getPOV();
  if(robot == NULL || goal == NULL)
    return MoveData();

  Alliance a = robot->getAlliance();
  Color c = static_cast<Color>(a);
  MoveData m;
  m.p = getPoints(s, a); // TODO: is there a more efficient way to do this?
  m.t = (goal->distFrom(*robot) / robot->avgSpeed); // TODO: implement better time factor estimate
  m.r = 1; // TODO: r value
  return m;
}

bool Claim::vexecute(SensorWrapper &sensorwrapper)
{
  Robot *robot = sensorwrapper.getPOV();
  if(robot == NULL || goal == NULL)
    return false;
  Color c = static_cast<Color>(robot->getAlliance());
  if(robot->numBalls(c) == 0 && goal->numBalls(c) == 0)
    return false;
  int i = 0;
  while(goal->topColor() != c && i < 100)
  {
    while(robot->numBalls(c) == 0 && robot->pushBall(goal->popBall())) {} // intake from the goal until you have a ball to score (or until you're full)
    while(goal->topColor() != c && goal->pushBall(robot->popBall())) {} // score in the goal until you have the goal (or until it's full)
    i++;
  }
  return goal->topColor() == c;
}

bool Claim::viable(SensorWrapper &sensorwrapper)
{
  Robot *robot = sensorwrapper.getPOV();
  if(robot == NULL || goal == NULL)
    return false;
  Color c = static_cast<Color>(robot->getAlliance());
  return (goal->topColor() != c) && // as long as the goal is not already ours
    (goal->numBalls(c) + robot->numBalls(c) > 0); // and a ball of our color is available to put on top
}

MoveData Cycle::getData(SensorWrapper &sensorwrapper)
{
  Robot *robot = sensorwrapper.getPOV();
  if(robot == NULL || goal == NULL)
    return MoveData();

  Color c = static_cast<Color>(robot->getAlliance());
  MoveData m;
  int ourTotalBalls = robot->numBalls(c) + goal->numBalls(c);
  int goalSize = goal->containerSize();
  m.p = goal->numBalls(!c) + (ourTotalBalls > goalSize ? goalSize : ourTotalBalls); // TODO: account for connected rows; number of opponent balls descored + (number of our balls scored up to 3)
  m.t = (goal->distFrom(*robot) / robot->avgSpeed); // TODO: implement better time factor estimate
  m.r = 1; // TODO: r value
  return m;
}

bool Cycle::vexecute(SensorWrapper &sensorwrapper)
{
  Robot *robot = sensorwrapper.getPOV();
  if(robot == NULL || goal == NULL)
    return false;
  // This isn't totally true-to-life, but it's faster
  // Essentially all of our balls (up to 3) end up in the goal and the rest end up in the robot, and all of theirs end up on the ground somewhere
  Color c = static_cast<Color>(robot->getAlliance());
  int totalBalls = robot->numBalls() + goal->numBalls();
  int ourTotalBalls = robot->numBalls(c) + goal->numBalls(c);
  const int GOAL_CAPACITY = goal->containerSize();

  robot->moveTo(*goal);

  // Dump / sort balls
  vector<Ball *> ourBalls, theirBalls;
  list<Ball *> temp = goal->dump();
  for(list<Ball *>::iterator it = temp.begin(); it != temp.end(); ++it)
  {
    if((*it)->getColor() == c)
      ourBalls.push_back(*it);
    else
      theirBalls.push_back(*it);
  }
  temp = robot->dump();
  for(list<Ball *>::iterator it = temp.begin(); it != temp.end(); ++it)
  {
    if((*it)->getColor() == c)
      ourBalls.push_back(*it);
    else
      theirBalls.push_back(*it);
  }

  // Put balls in the goal / robot
  if(ourBalls.size() <= GOAL_CAPACITY)
    for(vector<Ball *>::iterator it = ourBalls.begin(); it != ourBalls.end(); ++it)
      goal->pushBall(*it);
  else
  {
    vector<Ball *>::iterator it;
    for(it = ourBalls.begin(); it != ourBalls.begin() + GOAL_CAPACITY; ++it)
      goal->pushBall(*it);
    for( ; it != ourBalls.end(); ++it)
      robot->pushBall(*it);
  }

  // Scatter their balls elsewhere (TODO)
  //for(vector<Ball *>::iterator it = theirBalls.begin(); it != theirBalls.end(); ++it)

  return true; // TODO: are there any cases where this would fail?
}

bool Cycle::viable(SensorWrapper &sensorwrapper)
{
  Robot *robot = sensorwrapper.getPOV();
  if(robot == NULL || goal == NULL)
    return false;
  Color c = static_cast<Color>(robot->getAlliance());
  return goal->numBalls(!c) != 0 || // either the opposing alliance has some balls in the goal
    (!goal->full() && !robot->empty()); // or the goal is ours and we have more to score
}

MoveData Intake::getData(SensorWrapper &sensorwrapper)
{
  Robot *robot = sensorwrapper.getPOV();
  if(robot == NULL || ball == NULL)
    return MoveData();

  MoveData m;
  m.p = 0;
  m.t = ball->distFrom(*robot) / robot->avgSpeed; // TODO: implement better time factor estimate
  m.r = 1; // TODO: r value
  return m;
}

bool Intake::vexecute(SensorWrapper &sensorwrapper)
{
  Robot *robot = sensorwrapper.getPOV();
  if(robot == NULL || ball == NULL)
    return false;
  robot->moveTo(*ball);
  return robot->pushBall(ball);
}

bool Intake::viable(SensorWrapper &sensorwrapper)
{
  Robot *robot = sensorwrapper.getPOV();
  if(robot == NULL || ball == NULL)
    return false;
  return !robot->full();
}


#ifndef GENERATION_NO_ROBOT
// Instructions for execution with a physical robot via okapilib (TODO)

bool Claim::execute()
{

}

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

bool Claim::execute() { return false; }
bool Cycle::execute() { return false; }
bool Intake::execute() { return false; }
bool ZeroMove::execute() { return false; }

#endif
