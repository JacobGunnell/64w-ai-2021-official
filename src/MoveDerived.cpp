#include "MoveDerived.h"

colvec Cycle::vectorize()
{

}

bool Cycle::execute()
{

}

bool Cycle::vexecute(Robot *robot)
{

}

colvec Intake::vectorize()
{
  double P, T, Tnorm;
  P = 0;
  // TODO: implement time factor estimate
  return colvec{P, Tnorm};
}

bool Intake::execute()
{

}

bool Intake::vexecute(Robot *robot)
{
  robot->moveTo(ball->x, ball->y);
  return robot->pushBall(ball);
}
