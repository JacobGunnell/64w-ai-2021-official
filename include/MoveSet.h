#ifndef MOVESET_H
#define MOVESET_H


#include <vector>
using namespace std;

#include "Move.h"

class MoveSet : public Move // class for moves to be executed consecutively
{
public:
  MoveSet() : Move() {}
  MoveSet(vector<Move *>);
  MoveSet(Move **, int);
  ~MoveSet();

  vector<Move *> getMoves() const { return moves; }
  int size() const { return moves.size(); }
  void push(Move *m) { if(m != NULL) moves.push_back(m->clone()); }

  MoveData getData(Robot *) override;
  bool execute() override;
  bool vexecute(Robot *) override;
  bool viable(Robot *) override;

  Move *clone() override { return new MoveSet(moves); }

private:
  vector<Move *> moves;
};

#endif // MOVESET_H
