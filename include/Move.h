#ifndef MOVE_H
#define MOVE_H


#include "armadillo"
using namespace arma;
#include "SensorWrapper.h"
#include "Robot.h"
#include <cmath>

class Move
{
public:
  Move();
  ~Move();

  virtual colvec vectorize() = 0; // instructions to convert to vector form for AI consideration (TODO: expand vectors)
  virtual bool execute() = 0; // instructions to execute with a real robot
  virtual bool vexecute(Robot *) = 0; // instructions to execute on a virtual Robot

  static Move **getAllPossibleMoves(SensorWrapper);
  static mat getAllPossibleMovesMatrix(Move **, const int);
  static int getNumExistentMoves() { return numExistentMoves; }

private:
  static int numExistentMoves;
  static const double K;
};

#endif // MOVE_H
