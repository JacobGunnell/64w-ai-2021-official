#include "SensorWrapper.h"

SensorWrapper::SensorWrapper(GameObject **objs, int numObjs, int pov_)
{
  if(objs != NULL)
    for(int i = 0; i < numObjs; i++)
      if(objs[i] != NULL)
        push(objs[i]);
  if(pov_ < robots.size() && pov_ >= -1)
    pov = pov_;
}

SensorWrapper::SensorWrapper(const SensorWrapper &cpy)
{
  balls = cpy.balls;
  goals = cpy.goals;
  robots = cpy.robots;
  pov = cpy.pov;

  for(vector<Ball *>::iterator it = balls.begin(); it != balls.end(); ++it)
    *it = (*it)->clone();
  for(vector<Goal *>::iterator it = goals.begin(); it != goals.end(); ++it)
    *it = (*it)->clone();
  for(vector<Robot *>::iterator it = robots.begin(); it != robots.end(); ++it)
    *it = (*it)->clone();
}

SensorWrapper::~SensorWrapper()
{
  clear();
}

vector<Robot *> SensorWrapper::getRobots(Alliance a)
{
  vector<Robot *> r;
  for(vector<Robot *>::iterator it = robots.begin(); it != robots.end(); ++it)
    if((*it)->getAlliance() == a)
      r.push_back(*it);
  return r;
}
/*
Function to check for duplicates (possible issues)

#define _WRAPPER_DYNAMIC_PUSH(c, a) \
if(typeid(*obj) == typeid(c)) \
{ \
  for(vector<c *>::iterator it = a.begin(); it != a.end(); ++it) \
  { \
    if(**it == *reinterpret_cast<c *>(obj)) \
    { \
      dup = true; \ // TODO: fix
      break; \
    } \
  } \
  if(!dup) \
    a.push_back(reinterpret_cast<c *>(obj->clone())); \
  return; \
}

*/

#define _WRAPPER_DYNAMIC_PUSH(c, a) \
if(typeid(*obj) == typeid(c)) \
{ \
  a.push_back(reinterpret_cast<c *>(obj->clone())); \
  return; \
}

void SensorWrapper::push(GameObject *obj)
{
  if(obj != NULL)
  {
    bool dup = false;
    _WRAPPER_DYNAMIC_PUSH(Ball, balls)
    _WRAPPER_DYNAMIC_PUSH(Goal, goals)
    _WRAPPER_DYNAMIC_PUSH(Robot, robots)
  }
}

#define _WRAPPER_DYNAMIC_PUSH_NOCLONE(c, a) \
if(typeid(*obj) == typeid(c)) \
{ \
  a.push_back(reinterpret_cast<c *>(obj)); \
  return; \
}

void SensorWrapper::push_noclone(GameObject *obj)
{
  if(obj != NULL)
  {
    bool dup = false;
    _WRAPPER_DYNAMIC_PUSH_NOCLONE(Ball, balls)
    _WRAPPER_DYNAMIC_PUSH_NOCLONE(Goal, goals)
    _WRAPPER_DYNAMIC_PUSH_NOCLONE(Robot, robots)
  }
}

void SensorWrapper::append(vector<GameObject *> app)
{
  for(vector<GameObject *>::iterator it = app.begin(); it != app.end(); ++it)
    push(*it);
}

void SensorWrapper::append(vector<Ball *> app)
{
  for(vector<Ball *>::iterator it = app.begin(); it != app.end(); ++it)
    push(*it);
}

void SensorWrapper::append(vector<Goal *> app)
{
  for(vector<Goal *>::iterator it = app.begin(); it != app.end(); ++it)
    push(*it);
}

void SensorWrapper::append(vector<Robot *> app)
{
  for(vector<Robot *>::iterator it = app.begin(); it != app.end(); ++it)
    push(*it);
}

#define _WRAPPER_DYNAMIC_DELETE(c, a) \
for(vector<c *>::iterator it = a.begin(); it != a.end(); ++it) \
{ \
  delete *it; \
  *it = NULL; \
} \
a.clear();

void SensorWrapper::clear()
{
  _WRAPPER_DYNAMIC_DELETE(Ball, balls)
  _WRAPPER_DYNAMIC_DELETE(Goal, goals)
  _WRAPPER_DYNAMIC_DELETE(Robot, robots)
}

#define _WRAPPER_DYNAMIC_FIND_CONTAINED(c, g) \
if(typeid(*g) == typeid(c)) \
  return findContained(reinterpret_cast<c *>(g));

int SensorWrapper::findContained(GameObject *g)
{
  if(g == NULL)
    return -1;
  _WRAPPER_DYNAMIC_FIND_CONTAINED(Ball, g)
  _WRAPPER_DYNAMIC_FIND_CONTAINED(Goal, g)
  _WRAPPER_DYNAMIC_FIND_CONTAINED(Robot, g)
  return -1;
}

int SensorWrapper::findContained(Ball *g)
{
  for(int i = 0; i < balls.size(); i++)
    if(balls[i] == g)
      return i;
  return -1;
}

int SensorWrapper::findContained(Goal *g)
{
  for(int i = 0; i < goals.size(); i++)
    if(goals[i] == g)
      return i;
  return -1;
}

int SensorWrapper::findContained(Robot *g)
{
  for(int i = 0; i < robots.size(); i++)
    if(robots[i] == g)
      return i;
  return -1;
}

string SensorWrapper::print()
{
  string s;
  /*unordered_map<type_index, string> map;
  map[typeid(Ball *)] = "Ball";
  map[typeid(Goal *)] = "Goal";
  map[typeid(Robot *)] = "Robot";
  for(int i = 0; i < size(); i++)
  {
    GameObject *g = operator[](i);
    if(g != NULL)
      s += map[typeid(g)] + " at " + to_string(g->getX()) + ", " + to_string(g->getY()) + '\n';
  }*/
  for(vector<Ball *>::iterator it = balls.begin(); it != balls.end(); ++it)
    if(*it != NULL)
      s += string("Ball at ") + to_string((*it)->getX()) + ", " + to_string((*it)->getY()) + '\n';
  for(vector<Goal *>::iterator it = goals.begin(); it != goals.end(); ++it)
  {
    if(*it != NULL)
    {
      s += string("Goal at ") + to_string((*it)->getX()) + ", " + to_string((*it)->getY()) + '\n';
      list<Ball *> gb = (*it)->getBalls();
      for(list<Ball *>::reverse_iterator bit = gb.rbegin(); bit != gb.rend(); ++bit)
        if(*bit != NULL)
          s += string("  ") + ((*bit)->getColor() == RED ? "Red" : "Blue") + " Ball\n";
    }
  }
  for(vector<Robot *>::iterator it = robots.begin(); it != robots.end(); ++it)
    if(*it != NULL)
      s += string("Robot at ") + to_string((*it)->getX()) + ", " + to_string((*it)->getY()) + '\n';
  if(s.empty())
    s = "[empty]";
  return s;
}

SensorWrapper &SensorWrapper::operator+(SensorWrapper &rhs)
{
  static SensorWrapper s(*this);
  s.append(rhs.getBalls());
  s.append(rhs.getGoals());
  s.append(rhs.getRobots());
  return s;
}

GameObject *SensorWrapper::operator[](int i)
{
  // Treat the 3 vectors as a continuous array
  if(i >= 0 && i < balls.size())
    return balls.at(i);
  i -= balls.size();
  if(i >= 0 && i < goals.size())
    return goals.at(i);
  i -= goals.size();
  if(i >= 0 && i < robots.size())
    return robots.at(i);
  return NULL;
}
