#ifndef MOVE_H
#define MOVE_H


#include <armadillo>
using namespace arma;

class Move
{
public:
  Move();
  ~Move();

  colvec vectorize();
  bool execute();

  static Move *getAllPossibleMoves();
  static int numExistentObjects;
private:

};

#endif // MOVE_H
