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

colvec Move::vectorize()
{
  double P, T, S;
  // compute values
  return colvec{P, T, S};
}

bool Move::execute()
{

}

Move *Move::getAllPossibleMoves(SensorWrapper data)
{
  // TODO
  Move *m = new Move[100];
  return m;
}

mat Move::getAllPossibleMovesMatrix(SensorWrapper data)
{
  int before = getNumExistentMoves();
  Move *m = getAllPossibleMoves(data);
  int after = getNumExistentMoves();
  mat matrix;
  for(int i = 0; i < after - before; i++)
    matrix.insert_cols(i, m[i].vectorize());
  delete m;
  return matrix;
}
