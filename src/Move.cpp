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

Move **Move::getAllPossibleMoves(SensorWrapper data, double timeRemaining)
{
  // TODO
  Move **m = new Move*[100];
  return m;
}

arma::mat Move::toMatrix(Move **m, const int len, Robot *robot)
{
  arma::mat matrix;
  for(int i = 0; i < len; i++)
    matrix.insert_cols(i, m[i]->getData(robot).vectorize());
  return matrix;
}
