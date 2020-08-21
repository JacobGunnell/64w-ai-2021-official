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

MoveContainer::MoveContainer(SensorWrapper &s, double time)
{
  moves.push_back(new ZeroMove);

  //cout << "movecontainer ctor" << endl;
  vector<Goal *> g = s.getGoals();
  //cout << "goals: " << g.size() << endl;
  Move *m;
  for(vector<Goal *>::iterator it = g.begin(); it != g.end(); ++it)
  {
    m = new Claim(*it);
    if(m->viable(s))
    {
      //cout << "viable" << endl;
      moves.push_back(m);
    }
    else
      delete m;
  }

  /*
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
  */
}

MoveContainer::~MoveContainer()
{
  for(vector<Move *>::iterator it = moves.begin(); it != moves.end(); ++it)
  {
    delete *it;
    *it = NULL;
  }
}

void push(Move *m)
{
  // TODO: check for duplicates
}

void append(vector<Move *> m)
{
  // TODO
}

void append(Move **m, int len)
{
  // TODO
}

string MoveContainer::print()
{
  string s;
  unordered_map<type_index, string> map;
  map[typeid(ZeroMove)] = "ZeroMove";
  map[typeid(Claim)] = "Claim";
  map[typeid(Cycle)] = "Cycle";
  map[typeid(Intake)] = "Intake";
  map[typeid(MoveSet)] = "MoveSet";
  for(vector<Move *>::iterator it = moves.begin(); it != moves.end(); ++it)
  {
    Move *m = *it;
    if(m != NULL)
      s += map[typeid(*m)] + '\n';
  }
  return s;
}

Move *MoveContainer::operator[](int idx)
{
  if(idx < moves.size() && idx >= 0)
    return moves[idx];
  return NULL;
}
