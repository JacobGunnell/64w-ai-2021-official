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

arma::mat Move::toMatrix(MoveContainer m, Robot *robot)
{
  return toMatrix(m.moves, m.len, robot);
}
