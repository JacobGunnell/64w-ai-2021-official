#include "MoveContainer.h"

MoveContainer::MoveContainer(Move **moves_, int len_)
{
  if(moves_ != NULL)
  {
    moves = new Move *[len_];
    for(int i = 0; i < len_; i++)
    {
      if(moves_[i] != NULL)
        moves[i] = moves_[i]->clone();
      else
        moves[i] = new ZeroMove;
    }
  }
  else
  {
    moves = new Move *[1];
    moves[0] = new ZeroMove;
  }
}

MoveContainer::MoveContainer(SensorWrapper s, double time)
{
  const int NUM_EMPTY = 1;
  const int NUM_CONNECTABLE_ROWS = 8;

  const int TOTAL = NUM_EMPTY + NUM_CONNECTABLE_ROWS;
  moves = new Move *[TOTAL];

  moves[0] = new ZeroMove;

  for(int i = NUM_EMPTY; i < NUM_CONNECTABLE_ROWS; i++)
    moves[i] = new ConnectRow(i, reinterpret_cast<Goal **>(s.getObjs())); // TODO: fix!!
}

MoveContainer::~MoveContainer()
{
  for(int i = 0; i < len; i++)
    delete moves[i];
  delete [] moves;
}

Move *MoveContainer::operator[](int idx)
{
  if(idx < len && idx > 0 && moves[idx] != NULL)
    return moves[idx];
  else
    return new ZeroMove;
}
