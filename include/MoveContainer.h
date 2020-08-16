#ifndef MOVECONTAINER_H
#define MOVECONTAINER_H


#include <vector>
using namespace std;

#include "Move.h"
#include "MoveDerived.h"
#include "SensorWrapper.h"

class MoveContainer
{
public:
  MoveContainer() {}
  MoveContainer(vector<Move *>);
  MoveContainer(Move **, int);
  MoveContainer(SensorWrapper, Robot *, double);
  MoveContainer(const MoveContainer &cpy) : MoveContainer(cpy.moves) {}
  ~MoveContainer();

  vector<Move *> getMoves() const { return moves; }
  void push(Move *); // TODO: push function that checks for duplicates (maybe?)
  void append(vector<Move *>);
  void append(Move **, int);
  int size() const { return moves.size(); }

  Move *operator[](int);

  static MoveContainer getAllPossibleMoves(SensorWrapper s, Robot *r, double time) { return MoveContainer(s, r, time); }

private:
  vector<Move *> moves;

  friend class Move;
};

#include "MoveSet.h"

#endif // MOVECONTAINER_H
