#ifndef MOVE_H
#define MOVE_H


#include "armadillo"
#include "SensorWrapper.h"
#include "Robot.h"
#include <cmath>


struct MoveData
{
  int p; // how many points does this score?
  double t; // how long will it take?
  double KT = 2.71; // time normalization constant
  double r; // how sure are you that the move will finish?
  arma::colvec vectorize() { return arma::colvec{static_cast<double>(p), pow(KT, -t*t), r}; }
};

class Move
{
public:
  Move();
  virtual ~Move();

  virtual MoveData getData() = 0; // instructions to convert to vector form for AI consideration (TODO: expand vectors)
  virtual bool execute() = 0; // instructions to execute with a real robot
  virtual bool vexecute(Robot *) = 0; // instructions to execute on a virtual Robot

  static Move **getAllPossibleMoves(SensorWrapper, double = -1);
  static arma::mat toMatrix(Move **, const int);
  static int getNumExistentMoves() { return numExistentMoves; }

private:
  static int numExistentMoves;
};

#endif // MOVE_H
