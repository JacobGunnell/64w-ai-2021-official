#include "MoveDerived.h"

MoveData Cycle::getData()
{

}

bool Cycle::execute()
{

}

bool Cycle::vexecute(Robot *robot)
{

}

MoveData Intake::getData()
{
  
}

bool Intake::execute()
{

}

bool Intake::vexecute(Robot *robot)
{
  robot->moveTo(ball->x, ball->y);
  return robot->pushBall(ball);
}
