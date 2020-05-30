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

}

bool Move::execute()
{

}

Move *Move::getAllPossibleMoves()
{
  // TODO
  Move *m = new Move[100];
  return m;
}

mat Move::getAllPossibleMovesMatrix()
{

}
