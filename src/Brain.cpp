#include "Brain.h"

Brain *breed(Brain *mother, Brain *father)
{
  return NULL; // TODO
}


// everything below this line is ugly, but it was the only way

#include "SMP.h"
#include "SP.h"

#define _DYNAMIC_LOAD(c, s, e) \
if(e == c::getExtension()) \
{ \
  Brain *b = new c; \
  if(b->load(s)) \
    return b; \
  else \
    delete b; \
}

Brain *_dynamic_load(string file)
{
  string ext = file.substr(file.find_last_of('.'));
  _DYNAMIC_LOAD(SMP, file, ext) // add one of these macros for every derived class of Brain
  _DYNAMIC_LOAD(SP, file, ext)
  return NULL;
}
