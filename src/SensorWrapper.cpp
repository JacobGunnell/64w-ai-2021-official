#include "SensorWrapper.h"

SensorWrapper::SensorWrapper(GameObject **objs_, int numObjs_)
{
  if(objs_ != NULL)
  {
    numObjs = numObjs_;
    objs = new GameObject *[numObjs];
    for(int i = 0; i < numObjs; i++)
    {
      if(objs_[i] != NULL)
        objs[i] = new GameObject(*objs_[i]);
      else
        objs[i] = NULL;
    }
  }
  else
  {
    objs = NULL;
    numObjs = 0;
  }
}

SensorWrapper::SensorWrapper(const SensorWrapper &cpy)
{
  if(cpy.objs != NULL)
  {
    numObjs = cpy.numObjs;
    objs = new GameObject *[numObjs];
    for(int i = 0; i < numObjs; i++)
    {
      if(cpy.objs[i] != NULL)
        objs[i] = new GameObject(*cpy.objs[i]);
      else
        objs[i] = NULL;
    }
  }
  else
  {
    objs = NULL;
    numObjs = 0;
  }
}

SensorWrapper::~SensorWrapper()
{
  for(int i = 0; i < numObjs; i++)
    delete objs[i];
  delete [] objs;
}

SensorWrapper SensorWrapper::operator+(SensorWrapper rhs)
{
  GameObject **o = new GameObject*[numObjs + rhs.numObjs]; // allocate maximum required memory
  int i;
  for(i = 0; i < numObjs; i++) // fill with this wrapper's objects
    o[i] = objs[i];
  for(int j = 0; j < rhs.numObjs; j++) // fill with other wrapper's objects, checking for duplicates
  {
    bool dup = false;
    GameObject *object = rhs.objs[j];
    for(int k = 0; k < numObjs && !dup; k++)
      dup = objs[k] == object;
    if(!dup)
      o[i++] = object;
  }
  if(i < numObjs + rhs.numObjs)
    delete [] (o + i);
  return SensorWrapper(o, i);
}
