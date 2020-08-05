#ifndef MOVECONTAINER_H
#define MOVECONTAINER_H


#include "Move.h"
#include "MoveDerived.h"
#include "SensorWrapper.h"

class MoveContainer
{
public:
  MoveContainer() : moves(NULL), len(0) {}
  MoveContainer(Move **, int);
  MoveContainer(SensorWrapper, double);
  ~MoveContainer();

  int getLen() const { return len; }

  Move *operator[](int);

  static MoveContainer getAllPossibleMoves(SensorWrapper s, double time) { return MoveContainer(s, time); }

private:
  Move **moves;
  int len;

  friend class Move;
};

#endif // MOVECONTAINER_H
