#ifndef MOVE_H
#define MOVE_H


#include "armadillo"
using namespace arma;

class Move
{
public:
  Move();
  ~Move();

  colvec vectorize();
  bool execute();

  static Move *getAllPossibleMoves();
  static mat getAllPossibleMovesMatrix();
  static int getNumExistentMoves() { return numExistentMoves; }

private:
  static int numExistentMoves;
};

#endif // MOVE_H
