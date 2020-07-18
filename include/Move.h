#ifndef MOVE_H
#define MOVE_H


#include "armadillo"
using namespace arma;
#include "SensorWrapper.h"

class Move
{
public:
  Move();
  ~Move();

  colvec vectorize();
  bool execute();

  static Move *getAllPossibleMoves(SensorWrapper);
  static mat getAllPossibleMovesMatrix(SensorWrapper);
  static int getNumExistentMoves() { return numExistentMoves; }

private:
  static int numExistentMoves;
};

#endif // MOVE_H
