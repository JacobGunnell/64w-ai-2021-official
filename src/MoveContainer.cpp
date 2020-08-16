#include "MoveContainer.h"

MoveContainer::MoveContainer(vector<Move *> moves_)
{
  for(vector<Move *>::iterator it = moves_.begin(); it != moves_.end(); ++it)
    if(*it != NULL)
      moves.push_back((*it)->clone());
}

MoveContainer::MoveContainer(Move **moves_, int len_)
{
  if(moves_ != NULL)
  {
    for(int i = 0; i < len_; i++)
      if(moves_[i] != NULL)
        moves.push_back(moves_[i]->clone());
  }
  else
    moves.push_back(new ZeroMove);
}

MoveContainer::MoveContainer(SensorWrapper s, Robot *r, double time) // TODO: check to make sure move is viable (for instance, if row is already connected, omit that move)
{
  moves.push_back(new ZeroMove);

  // TODO: is there a better way to do this?
  // Iterate through all permutations of goals viable for scoring, including sets of 1, 2, and 3 goals (i'm very sorry.)
  vector<Goal *> g = s.getGoals();
  for(vector<Goal *>::iterator it0 = g.begin(); it0 != g.end(); ++it0)
  {
    MoveSet *mset1 = new MoveSet; // cycle 1 goal
    MoveSet *mset2 = new MoveSet; // cycle 2 goals
    MoveSet *mset3 = new MoveSet; // cycle 3 goals
    
    Move *m0 = new Cycle(*it0);
    if(m0->viable(r))
    {
      mset1->push(m0);
      moves.push_back(mset1);
      mset2->push(m0);
      mset3->push(m0);
    }
    else
    {
      delete m0;
      continue;
    }

    for(vector<Goal *>::iterator it1 = g.begin(); it1 != g.end(); ++it1)
    {
      if(it1 != it0)
      {
        Move *m1 = new Cycle(*it1);
        if(m1->viable(r))
        {
          mset2->push(m1);
          moves.push_back(mset2);
          mset3->push(m1);
        }
        else
        {
          delete m1;
          continue;
        }

        for(vector<Goal *>::iterator it2 = g.begin(); it2 != g.end(); ++it2)
        {
          if(it2 != it1 && it2 != it0)
          {
            Move *m2 = new Cycle(*it2);
            if(m2->viable(r))
            {
              mset3->push(m2);
              moves.push_back(mset3);
            }
            else
              delete m2;
          }
        }
      }
    }

  }

  /*Goal **g = s.getGoals().data();
  const int NUM_CONNECTABLE_ROWS = 8;
  for(int i = 0; i < NUM_CONNECTABLE_ROWS; i++)
    moves.push_back(new ConnectRow(i, g));*/
}

MoveContainer::~MoveContainer()
{
  for(vector<Move *>::iterator it = moves.begin(); it != moves.end(); ++it)
    delete *it;
}

Move *MoveContainer::operator[](int idx)
{
  if(idx < moves.size() && idx >= 0)
    return moves[idx];
  return NULL;
}
