#include "MoveDerived.h"

MoveData Cycle::getData()
{

}

bool Cycle::vexecute(Robot *robot)
{

}

MoveData Intake::getData()
{

}

bool Intake::vexecute(Robot *robot)
{
  robot->moveTo(ball->x, ball->y);
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
