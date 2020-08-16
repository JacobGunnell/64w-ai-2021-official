#ifndef MOVE_H
#define MOVE_H


#include "armadillo"
#include "SensorWrapper.h"
#include "Robot.h"
#include <cmath>


class MoveContainer;

struct MoveData
{
  int p = 0; // how many points does this score?
  double t = 0; // how long will it take?
  double r = 1; // how sure are you that the move will finish?
  static constexpr double KT = 2.71; // time normalization constant
  arma::rowvec vectorize() { return arma::rowvec{static_cast<double>(p), pow(KT, -t*t), r}; }
  MoveData operator+(MoveData &rhs) { return MoveData{p + rhs.p, t + rhs.t, r * rhs.r}; }
  MoveData &operator+=(MoveData rhs) { *this = *this + rhs; return *this; }
};

class Move
{
public:
  Move() {}
  virtual ~Move() {}

  virtual MoveData getData(Robot *) = 0; // instructions to convert to vector form for AI consideration (TODO: expand vectors)
  virtual bool execute() = 0; // instructions to execute with a real robot
  virtual bool vexecute(Robot *) = 0; // instructions to execute on a virtual Robot
  virtual bool viable(Robot *) = 0;

  virtual Move *clone() = 0;

  static arma::mat toMatrix(Move **, const int, Robot *);
  static arma::mat toMatrix(MoveContainer, Robot *);
};

#include "MoveContainer.h"

#endif // MOVE_H
