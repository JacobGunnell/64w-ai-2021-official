#include "MoveSet.h"

MoveSet::MoveSet(vector<Move *> moves_) : Move()
{
  for(vector<Move *>::iterator it = moves_.begin(); it != moves_.end(); ++it)
    if(*it != NULL)
      moves.push_back((*it)->clone());
}

MoveSet::MoveSet(Move **moves_, int len_) : Move()
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

MoveSet::~MoveSet()
{
  for(vector<Move *>::iterator it = moves.begin(); it != moves.end(); ++it)
    delete *it;
}

MoveData MoveSet::getData(Robot *robot)
{
  MoveData m;
  for(vector<Move *>::iterator it = moves.begin(); it != moves.end(); ++it)
    m += (*it)->getData(robot);
  return m;
}

bool MoveSet::execute()
{
  for(vector<Move *>::iterator it = moves.begin(); it != moves.end(); ++it)
    if(!(*it)->execute())
      return false;
  return true;
}

bool MoveSet::vexecute(Robot *robot)
{
  for(vector<Move *>::iterator it = moves.begin(); it != moves.end(); ++it)
    if(!(*it)->vexecute(robot))
      return false;
  return true;
}

bool MoveSet::viable(Robot *robot)
{
  for(vector<Move *>::iterator it = moves.begin(); it != moves.end(); ++it)
    if(!(*it)->viable(robot))
      return false;
  return true;
}
