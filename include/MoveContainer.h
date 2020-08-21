#ifndef MOVECONTAINER_H
#define MOVECONTAINER_H


#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <string>
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
  MoveContainer(SensorWrapper &, double);
  MoveContainer(const MoveContainer &cpy) : MoveContainer(cpy.moves) {}
  ~MoveContainer();

  vector<Move *> &getMoves() { return moves; }
  void push(Move *); // TODO: push function that checks for duplicates (maybe?)
  void append(vector<Move *>);
  void append(Move **, int);
  int size() const { return moves.size(); }
  bool empty() const { return moves.empty(); }

  string print();

  Move *operator[](int);
  operator string() { return print(); }

  static MoveContainer getAllPossibleMoves(SensorWrapper &s, double time) { return MoveContainer(s, time); }

private:
  vector<Move *> moves;

  friend class Move;
};

#include "MoveSet.h"

#endif // MOVECONTAINER_H
