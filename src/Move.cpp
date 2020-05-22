#include "Move.h"

int Move::numExistentObjects = 0;

Move::Move()
{
  numExistentObjects++;
}

Move::~Move()
{
  numExistentObjects--;
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
