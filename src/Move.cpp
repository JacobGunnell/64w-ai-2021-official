#include "Move.h"

int Move::numExistentMoves = 0;
const double Move::K = 2.7;

Move::Move()
{
  numExistentMoves++;
}

Move::~Move()
{
  numExistentMoves--;
}

Move **Move::getAllPossibleMoves(SensorWrapper data)
{
  // TODO
  Move **m = new Move*[100];
  return m;
}

mat Move::getAllPossibleMovesMatrix(Move **m, const int len)
{
  mat matrix;
  for(int i = 0; i < len; i++)
    matrix.insert_cols(i, m[i]->vectorize());
  return matrix;
}
