#include "Move.h"

int Move::numExistentMoves = 0;

Move::Move()
{
  numExistentMoves++;
}

Move::~Move()
{
  numExistentMoves--;
}

Move **Move::getAllPossibleMoves(SensorWrapper data, double timeRemaining) // TODO: move this to an external class (can't access derived classes from a base class function!)
{
  int len = 0;
  int lenmax = 0; // change!
  Move **m = new Move *[lenmax];
  // remember: include the zero move
  return m;
}

arma::mat Move::toMatrix(Move **m, const int len, Robot *robot)
{
  arma::mat matrix;
  if(m != NULL)
  {
    for(int i = 0; i < len; i++)
      if(m[i] != NULL)
        matrix.insert_cols(i, m[i]->getData(robot).vectorize());
      else
        matrix.insert_cols(i, MoveData().vectorize());
  }
  else
    matrix.reset();
  return matrix;
}
