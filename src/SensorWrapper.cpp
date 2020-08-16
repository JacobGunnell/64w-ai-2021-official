#include "SensorWrapper.h"

SensorWrapper::SensorWrapper(GameObject **objs, int numObjs)
{
  if(objs != NULL)
    for(int i = 0; i < numObjs; i++)
      if(objs[i] != NULL)
        push(objs[i]);
}

#define _WRAPPER_DYNAMIC_DELETE(c, a) \
for(vector<c *>::iterator it = a.begin(); it != a.end(); ++it) \
  delete *it;

SensorWrapper::~SensorWrapper()
{
  _WRAPPER_DYNAMIC_DELETE(Ball, balls)
  _WRAPPER_DYNAMIC_DELETE(Goal, goals)
  _WRAPPER_DYNAMIC_DELETE(Robot, robots)
}

#define _WRAPPER_DYNAMIC_PUSH(c, a) \
if(typeid(*obj) == typeid(c)) \
{ \
  for(vector<c *>::iterator it = a.begin(); it != a.end(); ++it) \
  { \
    if(**it == *reinterpret_cast<c *>(obj)) \
    { \
      dup = true; \
      break; \
    } \
  } \
  if(!dup) \
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

SensorWrapper SensorWrapper::operator+(SensorWrapper rhs)
{
  SensorWrapper s(*this);
  s.append(rhs.getBalls());
  s.append(rhs.getGoals());
  s.append(rhs.getRobots());
  return s;
}

GameObject *SensorWrapper::operator[](int i)
{
  // Treat the 3 vectors as a continuous array
  if(i >= 0 && i < balls.size())
    return balls[i];
  i -= balls.size();
  if(i >= 0 && i < goals.size())
    return goals[i];
  i -= goals.size();
  if(i >= 0 && i < robots.size())
    return robots[i];
  return NULL;
}
