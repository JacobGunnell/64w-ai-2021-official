#include "SensorWrapper.h"

SensorWrapper::SensorWrapper(GameObject **objs_, int numObjs)
{
  if(objs_ != NULL)
  {
    objs.reserve(numObjs);
    for(int i = 0; i < numObjs; i++)
    {
      if(objs_[i] != NULL)
        objs.push_back(objs_[i]->clone());
    }
  }
}

SensorWrapper::~SensorWrapper()
{
  for(vector<GameObject *>::iterator it = objs.begin(); it != objs.end(); ++it)
    delete *it;
}

void SensorWrapper::push(GameObject *obj)
{
  if(obj != NULL)
  {
    bool dup = false;
    for(vector<GameObject *>::iterator it = objs.begin(); it != objs.end(); ++it)
    {
      if(**it == *obj)
      {
        dup = true;
        break;
      }
    }
    if(!dup)
      objs.push_back(obj);
  }
}

void SensorWrapper::append(vector<GameObject *> app)
{
  for(vector<GameObject *>::iterator it = app.begin(); it != app.end(); ++it)
    push(*it);
}

SensorWrapper SensorWrapper::operator+(SensorWrapper rhs)
{
  GameObject **o = new GameObject*[objs.size() + rhs.objs.size()]; // allocate maximum required memory
  int i;
  for(i = 0; i < objs.size(); i++) // fill with this wrapper's objects
    o[i] = objs[i];
  for(int j = 0; j < rhs.objs.size(); j++) // fill with other wrapper's objects, checking for duplicates
  {
    bool dup = false;
    GameObject *object = rhs.objs[j];
    for(int k = 0; k < objs.size() && !dup; k++)
      dup = objs[k] == object;
    if(!dup)
      o[i++] = object;
  }
  SensorWrapper s(o, i);
  delete [] o;
  return s;
}
